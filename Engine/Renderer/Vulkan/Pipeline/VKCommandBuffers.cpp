// VKCommandBuffer.cpp
// Last update 16/8/2021 by Madman10K
#include <GL/glew.h>
#include "VKCommandBuffers.hpp"
#ifndef __APPLE__
#include <vulkan/vulkan.h>
#include <Core.hpp>
#include "VKDevice.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include "../Components/VKMesh.hpp"

void UVK::VKCommandBuffers::createCommandPool()
{
    auto queueFamilyIndices = device->getQueueFamilies();

    const VkCommandPoolCreateInfo poolInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .queueFamilyIndex = static_cast<uint32_t>(queueFamilyIndices.graphicsFamily),
    };

    if (vkCreateCommandPool(device->device.logicalDevice, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan Command Pool!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}

void UVK::VKCommandBuffers::destroyCommandPool()
{
    vkDestroyCommandPool(device->device.logicalDevice, commandPool, nullptr);
}

void UVK::VKCommandBuffers::createCommandbuffers()
{
    commandbuffers.resize(framebuffers->size());

    const VkCommandBufferAllocateInfo commandBufferAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = static_cast<uint32_t>(commandbuffers.size())
    };

    if (vkAllocateCommandBuffers(device->device.logicalDevice, &commandBufferAllocateInfo, commandbuffers.data()) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to allocate Vulkan Command Buffers", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}

void UVK::VKCommandBuffers::recordCommands(VKMesh& mesh, const std::vector<VkDescriptorSet>& descriptorSets)
{
    constexpr VkCommandBufferBeginInfo commandBufferBeginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };

    // Set up the clear colour, TODO: Add depth attachment
    const VkClearValue clearValues[1] = { { Level::getSceneColour().x, Level::getSceneColour().y, Level::getSceneColour().z, Level::getSceneColour().w } };

    VkRenderPassBeginInfo renderPassBeginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = *renderPass,
        .renderArea =
            {
                .offset = { 0, 0},
                .extent = { (uint32_t)Window::windowSize().x, (uint32_t)Window::windowSize().y }
            },
        .clearValueCount = 1,
        .pClearValues = clearValues
    };

    for (auto i = 0; i < commandbuffers.size(); i++)
    {
        renderPassBeginInfo.framebuffer = framebuffers->at(i).framebuffer;

        if (vkBeginCommandBuffer(commandbuffers[i], &commandBufferBeginInfo) != VK_SUCCESS)
        {
            logger.consoleLog("Failed to start recording the Vulkan Command Buffer", UVK_LOG_TYPE_ERROR);
            throw std::runtime_error(" ");
        }

        vkCmdBeginRenderPass(commandbuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandbuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, *graphicsPipeline);

        mesh.render(commandbuffers, i, descriptorSets);

        vkCmdEndRenderPass(commandbuffers[i]);

        if (vkEndCommandBuffer(commandbuffers[i]) != VK_SUCCESS)
        {
            logger.consoleLog("Failed to end the Vulkan Command Buffer recording!", UVK_LOG_TYPE_ERROR);
            throw std::runtime_error(" ");
        }
    }
}

UVK::VKCommandBuffers::VKCommandBuffers(UVK::Device* dev, std::vector<VKFramebuffer>& framebuf, VkPipeline* gp, VkRenderPass* rp)
{
    device = dev;
    framebuffers = &framebuf;
    graphicsPipeline = gp;
    renderPass = rp;
}

VkCommandPool& UVK::VKCommandBuffers::getCommandPool()
{
    return commandPool;
}

std::vector<VkCommandBuffer>& UVK::VKCommandBuffers::getCommandBuffers()
{
    return commandbuffers;
}

#endif