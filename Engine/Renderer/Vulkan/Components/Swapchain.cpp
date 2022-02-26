// Swapchain.cpp
// Last update 26/02/2022 by Madman10K
#include "Swapchain.hpp"
#include <glfw3.h>
#include <Core/Core/Global.hpp>


void UVK::Swapchain::createSurface()
{
    auto result = glfwCreateWindowSurface(instance->data(), global.window.getWindow(), nullptr, &surface);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a window surface! Error code: ", UVK_LOG_TYPE_ERROR, result);
        throw std::runtime_error(" ");
    }
}

void UVK::Swapchain::destroySurface()
{
    vkDestroySurfaceKHR(instance->data(), surface, nullptr);
}

UVK::Swapchain::Swapchain(UVK::VKInstance& inst, VKDevice& dev)
{
    instance = &inst;
    device = &dev;
}

VkSurfaceKHR& UVK::Swapchain::getSurface()
{
    return surface;
}

bool UVK::Swapchain::getSwapchainDetails(VkPhysicalDevice& dev)
{
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
