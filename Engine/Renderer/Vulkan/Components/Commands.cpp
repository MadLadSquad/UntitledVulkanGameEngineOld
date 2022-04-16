#include "Commands.hpp"
#include <Core/Global.hpp>
#include "Swapchain.hpp"
#include <Core/Actor.hpp>
#include <GameFramework/Components/Components.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <Renderer/Vulkan/VulkanRenderer.hpp>

void UVK::Commands::createCommandPool() noexcept
{
    const VkCommandPoolCreateInfo poolInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = static_cast<uint32_t>(device->getIndices().graphicsFamily),
    };

    const auto result = vkCreateCommandPool(device->getDevice(), &poolInfo, nullptr, &commandPool);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a Vulkan command pool! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

void UVK::Commands::destroyCommandPool() noexcept
{
    vkDestroyCommandPool(device->getDevice(), commandPool, nullptr);
}

void UVK::Commands::createCommandBuffers(size_t dependencySizeLink) noexcept
{
    commandBuffers.resize(dependencySizeLink);

    const VkCommandBufferAllocateInfo commandBufferAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = static_cast<uint32_t>(commandBuffers.size()),
    };

    const auto result = vkAllocateCommandBuffers(device->getDevice(), &commandBufferAllocateInfo, commandBuffers.data());
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to allocate the Vulkan command buffers! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

void UVK::Commands::destroyCommandBuffers() noexcept
{
    vkFreeCommandBuffers(device->getDevice(), commandPool, commandBuffers.size(), commandBuffers.data());
}

void UVK::Commands::draw() noexcept
{
    static uint32_t currentFrame = 0;
    uint32_t imageIndex;

    vkWaitForFences(device->getDevice(), 1, &fences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

    auto result = vkAcquireNextImageKHR(device->getDevice(), swapchain->getSwapchain(), std::numeric_limits<uint64_t>::max(), imageAvailable[currentFrame], VK_NULL_HANDLE, &imageIndex);
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR && result != VK_ERROR_OUT_OF_DATE_KHR)
    {
        logger.consoleLog("Couldn't acquire next image from the swapchain! Error code:", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    else if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        (*global.window.getRenderer())->recreate();
        return;
    }
    vkResetFences(device->getDevice(), 1, &fences[currentFrame]);
    recordCommands(imageIndex);

    auto& camera = UVK::Level::getPawn(global.currentLevel)->camera;
    VP vp =
    {
        .view = glm::lookAt(FVector(0.0f, 0.0f, -5.0f), FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f )),
        .projection = glm::perspective(glm::radians(90.0f), Window::windowSize().x / Window::windowSize().y, 0.1f, 100.0f)
        //.view = camera.calculateViewMatrix(),
        //.projection = camera.projection().data()
    };
    vp.projection[1][1] *= -1;

    resources->updateUniformBuffers(vp, imageIndex);
    constexpr VkPipelineStageFlags waitStages[] =
    {
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
    };
    const VkSubmitInfo submitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &imageAvailable[currentFrame],
        .pWaitDstStageMask = waitStages,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffers[imageIndex],
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &renderFinished[currentFrame]
    };
    result = vkQueueSubmit(device->getGraphicsQueue(), 1, &submitInfo, fences[currentFrame]);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't submit command buffer to the queue! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    const VkPresentInfoKHR presentInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &renderFinished[currentFrame],
        .swapchainCount = 1,
        .pSwapchains = &swapchain->getSwapchain(),
        .pImageIndices = &imageIndex
    };
    result = vkQueuePresentKHR(device->getPresentationQueue(), &presentInfo);
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR && result != VK_ERROR_OUT_OF_DATE_KHR)
    {
        logger.consoleLog("Failed to present the image! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    else if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || global.window.resized())
        (*global.window.getRenderer())->recreate();
    currentFrame = (currentFrame + 1) % VK_MAX_CONCURRENT_IMAGE_DRAW;
}

void UVK::Commands::recordCommands(uint32_t currentImage) noexcept
{
    constexpr VkCommandBufferBeginInfo commandBufferBeginInfo
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    };

    // TODO: Add depth attachment clear value
    const VkClearValue clearValues[] =
    {
        {
            .color = { global.colour.x, global.colour.y, global.colour.z, global.colour.w }
        },
        {
            .depthStencil =
            {
                .depth = 1.0f,
            }
        }
    };

    const VkRenderPassBeginInfo renderPassBeginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = pipeline->getRenderPass(),
        .framebuffer = swapchain->getFramebuffers()[currentImage],
        .renderArea =
        {
            .offset = { 0, 0 },
            .extent = swapchain->getExtent()
        },
        .clearValueCount = 2,
        .pClearValues = clearValues,
    };

    auto& a = commandBuffers[currentImage];
    auto result = vkBeginCommandBuffer(a, &commandBufferBeginInfo);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to start recording the Vulkan command buffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    vkCmdBeginRenderPass(a, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    const VkViewport viewport =
    {
        .x = 0.0f,
        .y = 0.0f,
        .width = static_cast<float>(swapchain->getExtent().width),
        .height = static_cast<float>(swapchain->getExtent().height),
        .minDepth = 0.0f,
        .maxDepth = 1.0f,
    };

    const VkRect2D scissor =
    {
        .offset = { 0, 0 },
        .extent = swapchain->getExtent()
    };
    vkCmdSetViewport(commandBuffers[currentImage], 0, 1, &viewport);
    vkCmdSetScissor(commandBuffers[currentImage], 0, 1, &scissor);

    vkCmdBindPipeline(a, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getPipeline());

    size_t f = 0;
    //ECS::forEveryComponent<MeshComponentRaw>([&](Actor& actor){
    //    auto& mesh = actor.get<MeshComponentRaw>();
    //    mesh.update(f, currentImage, *pipeline, *descriptors);
    //    f++;
    //});
    auto s = ECS::data().view<MeshComponentRaw>();
    for (auto& fn : s)
    {
        UVK::Actor actor(fn);
        auto& mesh = actor.get<MeshComponentRaw>();
        mesh.update(f, currentImage, *pipeline);
        f++;
    }
    auto fs = ECS::data().view<MeshComponent>();
    for (auto& fsn : fs)
    {
        UVK::Actor actor(fsn);
        actor.get<MeshComponent>().update(f, currentImage, *pipeline);
        f++;
    }

    //std::vector<VKMesh> meshes;
    //for (size_t f = 0; f < meshes.size(); f++)
    //{
    //    VkBuffer vertexBuffers[] = { meshes[f].getVertexBuffer().getBuffer() };
    //    VkDeviceSize offsets[] = { 0 };
//
    //    vkCmdBindVertexBuffers(commandBuffers[currentImage], 0, 1, vertexBuffers, offsets);
    //    vkCmdBindIndexBuffer(commandBuffers[currentImage], meshes[f].getIndexBuffer().getBuffer(), 0, VK_INDEX_TYPE_UINT32);
//
    //    //uint32_t dynamicOffset = static_cast<uint32_t>(modelUniformAlignment) * f;
    //    vkCmdPushConstants(commandBuffers[currentImage], pipeline->getPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(Model), &meshes[f].model);
    //    vkCmdBindDescriptorSets(commandBuffers[currentImage], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getPipelineLayout(), 0, 1, &descriptors->getDescriptorSets()[currentImage], 0, nullptr);
//
    //    vkCmdDrawIndexed(commandBuffers[currentImage], meshes[f].indexCount(), 1, 0, 0, 0);
    //}
//
    vkCmdEndRenderPass(a);

    result = vkEndCommandBuffer(a);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to stop recording the Vulkan command buffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

void UVK::Commands::createSynchronization() noexcept 
{
    imageAvailable.resize(VK_MAX_CONCURRENT_IMAGE_DRAW);
    renderFinished.resize(VK_MAX_CONCURRENT_IMAGE_DRAW);
    fences.resize(VK_MAX_CONCURRENT_IMAGE_DRAW);

    constexpr VkSemaphoreCreateInfo semaphoreCreateInfo
    {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    };

    constexpr VkFenceCreateInfo fenceCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT
    };

    for (size_t i = 0; i < VK_MAX_CONCURRENT_IMAGE_DRAW; i++)
    {
        auto result = vkCreateSemaphore(device->getDevice(), &semaphoreCreateInfo, nullptr, &imageAvailable[i]);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to create the image available Vulkan semaphore! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
        result = vkCreateSemaphore(device->getDevice(), &semaphoreCreateInfo, nullptr, &renderFinished[i]);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to create the render finished Vulkan semaphore! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
        result = vkCreateFence(device->getDevice(), &fenceCreateInfo, nullptr, &fences[i]);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to create a fence! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
    }
}

void UVK::Commands::destroySynchronization() noexcept 
{
    for (size_t i = 0; i < VK_MAX_CONCURRENT_IMAGE_DRAW; i++)
    {
        vkDestroyFence(device->getDevice(), fences[i], nullptr);
        vkDestroySemaphore(device->getDevice(), imageAvailable[i], nullptr);
        vkDestroySemaphore(device->getDevice(), renderFinished[i], nullptr);
    }
}

UVK::Commands::Commands(UVK::VKDevice& dev, UVK::Swapchain& swap, UVK::GraphicsPipeline& graphicsPipeline, UVK::VKDescriptors& desc, UVK::VKResources& res)
{
    device = &dev;
    swapchain = &swap;
    pipeline = &graphicsPipeline;
    descriptors = &desc;
    resources = &res;
}

VkCommandPool& UVK::Commands::getCommandPool() noexcept
{
    return commandPool;
}

const std::vector<VkCommandBuffer>& UVK::Commands::getCommandBuffers() const noexcept
{
    return commandBuffers;
}
