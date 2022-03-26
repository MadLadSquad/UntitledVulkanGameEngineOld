#include "Swapchain.hpp"
#include <glfw3.h>
#include <Core/Core/Global.hpp>
#include "GraphicsPipeline.hpp"

void UVK::Swapchain::createSurface() noexcept
{
    auto result = glfwCreateWindowSurface(instance->data(), global.window.getWindow(), nullptr, &surface);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a window surface! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

void UVK::Swapchain::destroySurface() noexcept
{
    vkDestroySurfaceKHR(instance->data(), surface, nullptr);
}

UVK::Swapchain::Swapchain(UVK::VKInstance& inst, VKDevice& dev) noexcept
{
    instance = &inst;
    device = &dev;
}

VkSurfaceKHR& UVK::Swapchain::getSurface() noexcept
{
    return surface;
}

bool UVK::Swapchain::getSwapchainDetails(VkPhysicalDevice& dev, const QueueFamilyIndices& indices) noexcept
{
    VkBool32 bSupportedPresentation;
    vkGetPhysicalDeviceSurfaceSupportKHR(dev, indices.graphicsFamily, surface, &bSupportedPresentation);

    if (bSupportedPresentation == VK_FALSE)
        return false;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, surface, &details.surfaceCapabilities);
    uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface, &formatCount, nullptr);

    bool bReturn = true;
    if (formatCount != 0)
    {
        details.surfaceFormats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface, &formatCount, details.surfaceFormats.data());
    }
    else
        bReturn = false;
    uint32_t presentationCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface, &presentationCount, nullptr);

    if (presentationCount != 0)
    {
        details.presentationModes.resize(presentationCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface, &presentationCount, details.presentationModes.data());
    }
    else
        bReturn = false;

    return bReturn;
}

UVK::Swapchain::~Swapchain() noexcept
{
    static bool bFirst = true;
    if (bFirst)
        bFirst = false;
    else
        destroySurface();
}

void UVK::Swapchain::createSwapchain() noexcept
{
    // TODO: check this function for resize
    //getSwapchainDetails(device->physicalDevice);
    determineSurfaceFormats();
    determinePresentationMode();
    determineExtent();

    const uint32_t imageCount = details.surfaceCapabilities.maxImageCount > 0 && details.surfaceCapabilities.maxImageCount < (details.surfaceCapabilities.minImageCount + 1) ? details.surfaceCapabilities.maxImageCount : details.surfaceCapabilities.minImageCount + 1;
    VkSharingMode sharingMode;
    uint32_t queueFamilyIndexCount;
    uint32_t queueFamilyIndices[2];

    if (device->indices.graphicsFamily != device->indices.presentationFamily)
    {
        sharingMode = VK_SHARING_MODE_CONCURRENT;
        queueFamilyIndexCount = 2;
        queueFamilyIndices[0] = static_cast<uint32_t>(device->indices.graphicsFamily);
        queueFamilyIndices[1] = static_cast<uint32_t>(device->indices.presentationFamily);
    }
    else
    {
        sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        queueFamilyIndexCount = 0;

        // ugh assign array to nullptr
        auto** ptr = reinterpret_cast<uint32_t**>(&queueFamilyIndices);
        *ptr = nullptr;
    }

    const VkSwapchainCreateInfoKHR swapchainCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = surface,
        .minImageCount = imageCount, // For triple buffering
        .imageFormat = surfaceFormat.format,
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = sharingMode,
        .queueFamilyIndexCount = queueFamilyIndexCount,
        .pQueueFamilyIndices = queueFamilyIndices,
        .preTransform = details.surfaceCapabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentationMode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE // TODO: Check this for window resizing
    };

    auto result = vkCreateSwapchainKHR(device->device, &swapchainCreateInfo, nullptr, &swapchain);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a swapchain! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    uint32_t swapchainImageCount;
    vkGetSwapchainImagesKHR(device->device, swapchain, &swapchainImageCount, nullptr);
    std::vector<VkImage> tmpImages(swapchainImageCount);
    vkGetSwapchainImagesKHR(device->device, swapchain, &swapchainImageCount, tmpImages.data());

    for (const VkImage& image : tmpImages)
    {
        images.push_back({
            image,
            createImageView(image, surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT)
        });
    }
}

void UVK::Swapchain::destroySwapchain() noexcept
{
    for (const auto& a : images)
        vkDestroyImageView(device->device, a.imageView, nullptr);
    vkDestroySwapchainKHR(device->device, swapchain, nullptr);
}

void UVK::Swapchain::determineSurfaceFormats() noexcept
{
    if (details.surfaceFormats.size() == 1 && details.surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
    {
        surfaceFormat.format = VK_FORMAT_R8G8B8A8_UNORM;
        surfaceFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        return;
    }

    for (auto& a : details.surfaceFormats)
    {
        if ((a.format == VK_FORMAT_R8G8B8A8_UNORM || a.format == VK_FORMAT_B8G8R8A8_UNORM) && a.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            surfaceFormat = a;
            return;
        }
    }
    surfaceFormat = details.surfaceFormats[0];
}

void UVK::Swapchain::determinePresentationMode() noexcept
{
    for (auto& a : details.presentationModes)
    {
        if ((a == VK_PRESENT_MODE_IMMEDIATE_KHR && !global.rendererSettings.bVsync && !global.bEditor) || (a == VK_PRESENT_MODE_MAILBOX_KHR && (global.rendererSettings.bVsync || global.bEditor)))
        {
            presentationMode = a;
            return;
        }
    }
    presentationMode = VK_PRESENT_MODE_FIFO_KHR;
}

void UVK::Swapchain::determineExtent() noexcept
{
    if (details.surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        extent = details.surfaceCapabilities.currentExtent;
    }
    else
    {
        int width, height;
        glfwGetFramebufferSize(global.window.getWindow(), &width, &height);

        extent = VkExtent2D
        {
            .width = static_cast<uint32_t>(width),
            .height = static_cast<uint32_t>(height)
        };

        extent.width = std::max(details.surfaceCapabilities.minImageExtent.width, std::min(details.surfaceCapabilities.maxImageExtent.width, extent.width));
        extent.height = std::max(details.surfaceCapabilities.minImageExtent.height, std::min(details.surfaceCapabilities.maxImageExtent.height, extent.height));
    }
}

VkImageView UVK::Swapchain::createImageView(const VkImage& image, const VkFormat& format, const VkImageAspectFlags& aspectFlags) noexcept
{
    const VkImageViewCreateInfo viewCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = image,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = format,
        .components =
        {
            .r = VK_COMPONENT_SWIZZLE_IDENTITY,
            .g = VK_COMPONENT_SWIZZLE_IDENTITY,
            .b = VK_COMPONENT_SWIZZLE_IDENTITY,
            .a = VK_COMPONENT_SWIZZLE_IDENTITY
        },
        .subresourceRange =
        {
            .aspectMask = aspectFlags,
            .baseMipLevel = 0,
            .levelCount = 1,
            .baseArrayLayer = 0,
            .layerCount = 1
        },
    };

    VkImageView imageView;
    auto result = vkCreateImageView(device->device, &viewCreateInfo, nullptr, &imageView);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create an image view! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    return imageView;
}

void UVK::Swapchain::createFramebuffers(GraphicsPipeline& graphicsPipeline) noexcept
{
    pipeline = &graphicsPipeline;
    framebuffers.resize(images.size());

    for (size_t i = 0; i < framebuffers.size(); i++)
    {
        // Should be an array
        const VkImageView attachments[1] = { images[i].imageView };
        const VkFramebufferCreateInfo framebufferCreateInfo =
        {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = pipeline->renderPass,
            .attachmentCount = 1,
            .pAttachments = attachments,
            .width = extent.width,
            .height = extent.height,
            .layers = 1
        };

        auto result = vkCreateFramebuffer(device->device, &framebufferCreateInfo, nullptr, &framebuffers[i]);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to create a Vulkan framebuffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
    }
}

void UVK::Swapchain::destroyFramebuffers() noexcept
{
    for (auto& a : framebuffers)
        vkDestroyFramebuffer(device->device, a, nullptr);
}

void UVK::Swapchain::createCommandPool() noexcept
{
    const VkCommandPoolCreateInfo poolInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .queueFamilyIndex = static_cast<uint32_t>(device->indices.graphicsFamily),
    };

    auto result = vkCreateCommandPool(device->device, &poolInfo, nullptr, &commandPool);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a Vulkan command pool! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

void UVK::Swapchain::destroyCommandPool() noexcept
{
    vkDestroyCommandPool(device->device, commandPool, nullptr);
}

void UVK::Swapchain::createCommandBuffers() noexcept
{
    commandBuffers.resize(framebuffers.size());

    const VkCommandBufferAllocateInfo commandBufferAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = static_cast<uint32_t>(commandBuffers.size()),
    };

    auto result = vkAllocateCommandBuffers(device->device, &commandBufferAllocateInfo, commandBuffers.data());
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to allocate the Vulkan command buffers! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

void UVK::Swapchain::destroyCommandBuffers() noexcept
{

}

void UVK::Swapchain::recordCommands(std::vector<VKMesh>& meshes) noexcept
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
        }
    };

    VkRenderPassBeginInfo renderPassBeginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = pipeline->renderPass,
        .renderArea =
        {
            .offset = { 0, 0 },
            .extent = extent
        },
        .clearValueCount = 1,
        .pClearValues = clearValues,
    };

    for (size_t i = 0; i < commandBuffers.size(); i++)
    {
        renderPassBeginInfo.framebuffer = framebuffers[i];

        auto& a = commandBuffers[i];
        auto result = vkBeginCommandBuffer(a, &commandBufferBeginInfo);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to start recording the Vulkan command buffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->graphicsPipeline);

        for (auto& f : meshes)
        {
            VkBuffer vertexBuffers[] = { f.getVertexBuffer() };
            VkDeviceSize offsets[] = { 0 };

            vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
            vkCmdDraw(commandBuffers[i], static_cast<uint32_t>(f.vertexCount()), 1, 0, 0);
        }



        vkCmdEndRenderPass(commandBuffers[i]);

        result = vkEndCommandBuffer(a);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to stop recording the Vulkan command buffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
    }
}

void UVK::Swapchain::draw() noexcept
{
    static uint32_t currentFrame = 0;

    vkWaitForFences(device->device, 1, &fences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());
    vkResetFences(device->device, 1, &fences[currentFrame]);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(device->device, swapchain, std::numeric_limits<uint64_t>::max(), imageAvailable[currentFrame], VK_NULL_HANDLE, &imageIndex);

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

    auto result = vkQueueSubmit(device->queue, 1, &submitInfo, fences[currentFrame]);
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
        .pSwapchains = &swapchain,
        .pImageIndices = &imageIndex
    };

    result = vkQueuePresentKHR(device->presentationQueue, &presentInfo);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to present the image! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    currentFrame = (currentFrame + 1) % VK_MAX_CONCURRENT_IMAGE_DRAW;
}

void UVK::Swapchain::createSynchronisation() noexcept
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
        auto result = vkCreateSemaphore(device->device, &semaphoreCreateInfo, nullptr, &imageAvailable[i]);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to create the image available Vulkan semaphore! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
        result = vkCreateSemaphore(device->device, &semaphoreCreateInfo, nullptr, &renderFinished[i]);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to create the render finished Vulkan semaphore! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
        result = vkCreateFence(device->device, &fenceCreateInfo, nullptr, &fences[i]);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to create a fence! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
    }
}

void UVK::Swapchain::destroySynchronisation() noexcept
{
    for (size_t i = 0; i < VK_MAX_CONCURRENT_IMAGE_DRAW; i++)
    {
        vkDestroyFence(device->device, fences[i], nullptr);
        vkDestroySemaphore(device->device, imageAvailable[i], nullptr);
        vkDestroySemaphore(device->device, renderFinished[i], nullptr);
    }
}
