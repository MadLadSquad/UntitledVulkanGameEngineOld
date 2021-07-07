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
    auto settings = getSwapchainSettings();

    auto surfaceFormat = findSurfaceFormat(settings.formats);
    auto presentMode = findPresentationMode(settings.presentationModes);
    auto extent = findSwapchainExtent(settings.surfaceCapabilities);

    // +1 to allow for triple buffering
    uint32_t minImageCount = settings.surfaceCapabilities.minImageCount + 1;
    if (settings.surfaceCapabilities.maxImageCount < minImageCount && settings.surfaceCapabilities.maxImageCount > 0)
    {
        --minImageCount;
    }

    VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
    swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCreateInfo.surface = surface;
    swapchainCreateInfo.imageFormat = surfaceFormat.format;
    swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
    swapchainCreateInfo.presentMode = presentMode;
    swapchainCreateInfo.imageExtent = extent;
    swapchainCreateInfo.minImageCount = minImageCount;
    swapchainCreateInfo.imageArrayLayers = 1;
    swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchainCreateInfo.preTransform = settings.surfaceCapabilities.currentTransform;
    swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainCreateInfo.clipped = VK_TRUE;

    auto location = device->getQueueFamilies();

    uint32_t queueFamilyIndices[] = { (uint32_t)location.graphicsFamily, (uint32_t)location.presentationFamily };
    if (location.graphicsFamily != location.presentationFamily)
    {

        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchainCreateInfo.queueFamilyIndexCount = 2;
        swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.queueFamilyIndexCount = 0;
        swapchainCreateInfo.pQueueFamilyIndices = nullptr;
    }

    swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

    auto result = vkCreateSwapchainKHR(device->getDevice().logicalDevice, &swapchainCreateInfo, nullptr, &swapchain);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create the Vulkan swapchain!", UVK_LOG_TYPE_ERROR);
    }

    swapchainFormat = surfaceFormat.format;
    swapchainExtent = extent;

    uint32_t swapchainImageCount;
    vkGetSwapchainImagesKHR(device->getDevice().logicalDevice, swapchain, &swapchainImageCount, nullptr);
    std::vector<VkImage> imgs(swapchainImageCount);
    vkGetSwapchainImagesKHR(device->getDevice().logicalDevice, swapchain, &swapchainImageCount, imgs.data());

    for (auto& a : imgs)
    {
        VKSwapchainImage swapchainImage = {};
        swapchainImage.image = a;
        swapchainImage.imageView = createImageView(swapchainImage.image, swapchainFormat, VK_IMAGE_ASPECT_COLOR_BIT);

        images.push_back(swapchainImage);
    }
}

void UVK::VKSwapchain::destroySwapchain()
{
    for (auto& a : images)
    {
        vkDestroyImageView(device->getDevice().logicalDevice, a.imageView, nullptr);
    }
    vkDestroySwapchainKHR(device->getDevice().logicalDevice, swapchain, nullptr);
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

VkSurfaceFormatKHR UVK::VKSwapchain::findSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats)
{
    VkSurfaceFormatKHR fmt;

    // Unlike what the name implies VK_FORMAT_UNDEFINED means that we support everything so we return the best
    if (formats.size() == 1 && formats[0].format == VK_FORMAT_UNDEFINED)
    {
        // OK for now since AdobeRGB still uses 8 bits as said here
        fmt.format = VK_FORMAT_R8G8B8A8_UNORM;
        // Probably the best colour space available
        fmt.colorSpace = VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT;

        return fmt;
    }

    for (const auto& format : formats)
    {
        if (format.format == VK_FORMAT_R8G8B8A8_UNORM || format.format == VK_FORMAT_B8G8R8A8_UNORM)
        {
            if (format.colorSpace == VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT || format.colorSpace == VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT || format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return format;
            }
        }
    }

    // Return the first one and hope for the best
    return formats[0];
}

VkPresentModeKHR UVK::VKSwapchain::findPresentationMode(const std::vector<VkPresentModeKHR> &modes)
{
    for (const auto& mode : modes)
    {
        // Best mode type
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return mode;
        }
    }

    // Always available if the device supports Vulkan
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D UVK::VKSwapchain::findSwapchainExtent(const VkSurfaceCapabilitiesKHR& surfaceCapabilities)
{
    if (surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return surfaceCapabilities.currentExtent;
    }

    VkExtent2D extent;
    extent.width = global.window.getBufferWidth();
    extent.height = global.window.getBufferHeight();

    extent.width = std::max(surfaceCapabilities.minImageExtent.width, std::min(surfaceCapabilities.maxImageExtent.width, extent.width));
    extent.height = std::max(surfaceCapabilities.minImageExtent.height, std::min(surfaceCapabilities.maxImageExtent.height, extent.height));

    return extent;
}

VkImageView UVK::VKSwapchain::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
{
    VkImageViewCreateInfo viewCreateInfo = {};
    viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewCreateInfo.format = format;
    viewCreateInfo.image = image;
    viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.subresourceRange.aspectMask = aspectFlags;
    viewCreateInfo.subresourceRange.baseArrayLayer = 0;
    viewCreateInfo.subresourceRange.baseMipLevel = 0;
    viewCreateInfo.subresourceRange.layerCount = 1;
    viewCreateInfo.subresourceRange.levelCount = 1;

    VkImageView imageView;
    auto result = vkCreateImageView(device->getDevice().logicalDevice, &viewCreateInfo, nullptr, &imageView);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan image view", UVK_LOG_TYPE_ERROR);
    }

    return imageView;
}
#endif