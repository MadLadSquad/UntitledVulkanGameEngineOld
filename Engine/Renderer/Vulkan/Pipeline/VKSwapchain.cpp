// VKSwapchain.cpp
// Last update 2/7/2021 by Madman10K
#ifndef __APPLE__
#include <GL/glew.h>
#define GLFW_INCLUDE_VULKAN
#include <Engine/Core/Core/Global.hpp>
#include <Core.hpp>
#include <GLFW/glfw3.h>
#include "VKSwapchain.hpp"
#include "VKDevice.hpp"
#include <Renderer/Window/Window.hpp>


void UVK::VKSwapchain::createSurface()
{
    auto result = glfwCreateWindowSurface(instance->getData(), global.window.getWindow(), nullptr, &surface);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a Vulkan surface!", UVK_LOG_TYPE_ERROR);
    }
}

void UVK::VKSwapchain::destroySurface()
{
    vkDestroySurfaceKHR(instance->getData(), surface, nullptr);
}

void UVK::VKSwapchain::createSwapchain()
{
    VKSwapchainSettings settings = getSwapchainSettings();

    // Choose best format for surface
}

void UVK::VKSwapchain::destroySwapchain()
{

}

UVK::VKSwapchainSettings UVK::VKSwapchain::getSwapchainSettings()
{
    uint32_t formatCount = 0;

    VKSwapchainSettings settings = {};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->getDevice().physicalDevice, surface, &settings.surfaceCapabilities);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device->getDevice().physicalDevice, surface, &formatCount, nullptr);

    if (formatCount != 0)
    {
        settings.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device->getDevice().physicalDevice, surface, &formatCount, settings.formats.data());
    }

    uint32_t presentationCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device->getDevice().physicalDevice, surface, &presentationCount, nullptr);

    if (presentationCount != 0)
    {
        settings.presentationModes.resize(presentationCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device->getDevice().physicalDevice, surface, &presentationCount, settings.presentationModes.data());
    }

    return settings;
}

void UVK::VKSwapchain::set(UVK::VKInstance* inst, UVK::Device* dev)
{
    instance = inst;
    device = dev;
}
#endif
