// VKDraw.cpp
// Last update 16/8/2021 by Madman10K
#include "VKDraw.hpp"
#include <Core.hpp>
#include "VKDevice.hpp"
#include "VKSwapchain.hpp"
#include "VKCommandBuffers.hpp"

void UVK::VKDraw::createSynchronisation()
{
    imageAvailable.resize(VK_MAX_CONCURRENT_IMAGE_DRAW);
    finishedRendering.resize(VK_MAX_CONCURRENT_IMAGE_DRAW);
    fences.resize(VK_MAX_CONCURRENT_IMAGE_DRAW);

    VkSemaphoreCreateInfo semaphoreCreateInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
    VkFenceCreateInfo fenceCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT
    };

    for (auto i = 0; i < VK_MAX_CONCURRENT_IMAGE_DRAW; i++)
    {
        if (vkCreateSemaphore(device->device.logicalDevice, &semaphoreCreateInfo, nullptr, &finishedRendering[i]) != VK_SUCCESS || vkCreateSemaphore(device->device.logicalDevice, &semaphoreCreateInfo, nullptr, &imageAvailable[i]) != VK_SUCCESS || vkCreateFence(device->device.logicalDevice, &fenceCreateInfo, nullptr, &fences[i]) != VK_SUCCESS)
        {
            logger.consoleLog("Failed to create Vulkan Semaphores and/or Fences!", UVK_LOG_TYPE_ERROR);
            throw std::runtime_error(" ");
        }
    }
}

void UVK::VKDraw::destroySynchronisasion()
{
    // Wait until there is nothing on the queue and then destroy semaphores
    vkDeviceWaitIdle(device->device.logicalDevice);

    for (auto i = 0; i < VK_MAX_CONCURRENT_IMAGE_DRAW; i++)
    {
        vkDestroyFence(device->device.logicalDevice, fences[i], nullptr);
        vkDestroySemaphore(device->device.logicalDevice, finishedRendering[i], nullptr);
        vkDestroySemaphore(device->device.logicalDevice, imageAvailable[i], nullptr);
    }
}

void UVK::VKDraw::getNextImage()
{
    vkWaitForFences(device->device.logicalDevice, 1, &fences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());
    vkResetFences(device->device.logicalDevice, 1, &fences[currentFrame]);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(device->device.logicalDevice, swapchain->swapchain, std::numeric_limits<uint64_t>::max(), imageAvailable[currentFrame], VK_NULL_HANDLE, &imageIndex);

    constexpr VkPipelineStageFlags waitStages[1] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    VkSubmitInfo submitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &imageAvailable[currentFrame],
        .pWaitDstStageMask = waitStages,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffers->commandbuffers[imageIndex],
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &finishedRendering[currentFrame]
    };

    if (vkQueueSubmit(device->queue, 1, &submitInfo, fences[currentFrame]) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to submit to Vulkan Graphics Queue!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    VkPresentInfoKHR presentInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &finishedRendering[currentFrame],
        .swapchainCount = 1,
        .pSwapchains = &swapchain->swapchain,
        .pImageIndices = &imageIndex
    };

    if (vkQueuePresentKHR(device->presentationQueue, &presentInfo) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to present to Vulkan Presentation Queue!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    currentFrame = (currentFrame + 1) % VK_MAX_CONCURRENT_IMAGE_DRAW;
}

UVK::VKDraw::VKDraw(UVK::Device* dev, UVK::VKSwapchain* sw, UVK::VKCommandBuffers* cmd)
{
    device = dev;
    swapchain = sw;
    commandBuffers = cmd;
}
