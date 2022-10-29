#include "Swapchain.hpp"
#include <glfw3.h>
#include <Core/Core/Global.hpp>
#include "GraphicsPipeline.hpp"
#include "Depth.hpp"

void UVK::Swapchain::createSurface() noexcept
{
    const auto result = glfwCreateWindowSurface(instance->data(), global.window.getWindow(), nullptr, &surface);
    if (result != VK_SUCCESS)
    {
        Logger::log("Failed to create a window surface! Error code: ", UVK_LOG_TYPE_ERROR, result);
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

void UVK::Swapchain::createSwapchain(VkSwapchainKHR oldswapchain) noexcept
{
    // TODO: check this function for resize
    getSwapchainDetails(device->physicalDevice, device->getIndices());
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
        .oldSwapchain = oldswapchain
    };

    const auto result = vkCreateSwapchainKHR(device->device, &swapchainCreateInfo, nullptr, &swapchain);
    if (result != VK_SUCCESS)
    {
        Logger::log("Failed to create a swapchain! Error code: ", UVK_LOG_TYPE_ERROR, result);
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
        });
        images.back().createImageView(surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT, *device);
    }
}

void UVK::Swapchain::destroySwapchain(bool bNoDestroy) noexcept
{
    for (const auto& a : images)
        vkDestroyImageView(device->device, a.imageView, nullptr);
    if (!bNoDestroy)
        vkDestroySwapchainKHR(device->device, swapchain, nullptr);
    images.clear();
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
        // Choose our desired colour format
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

void UVK::Swapchain::createFramebuffers(GraphicsPipeline& graphicsPipeline) noexcept
{
    pipeline = &graphicsPipeline;
    framebuffers.resize(images.size());

    for (size_t i = 0; i < framebuffers.size(); i++)
    {
        uint32_t attachmentCount = 3;
        std::array<VkImageView, 3> msaaAttachments = { colourImage.imageView, depthBuffer->getImage().imageView, images[i].imageView };
        std::array<VkImageView, 2> nomsaaAttachments = { images[i].imageView, depthBuffer->getImage().imageView };

        VkImageView* attachment = msaaAttachments.data();
        if (UVK::Renderer::msaaSampleCount() >= 0 && UVK::Renderer::msaaSampleCount() < 2)
        {
            attachmentCount = 2;
            attachment = nomsaaAttachments.data();
        }

        const VkFramebufferCreateInfo framebufferCreateInfo =
        {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = pipeline->renderPass,
            .attachmentCount = attachmentCount,
            .pAttachments = attachment,
            .width = extent.width,
            .height = extent.height,
            .layers = 1
        };

        const auto result = vkCreateFramebuffer(device->device, &framebufferCreateInfo, nullptr, &framebuffers[i]);
        if (result != VK_SUCCESS)
        {
            Logger::log("Failed to create a Vulkan framebuffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
    }
}

void UVK::Swapchain::destroyFramebuffers() noexcept
{
    for (auto& a : framebuffers)
        vkDestroyFramebuffer(device->device, a, nullptr);
    framebuffers.clear();
}

const std::vector<VkFramebuffer>& UVK::Swapchain::getFramebuffers() const noexcept
{
    return framebuffers;
}

VkSwapchainKHR& UVK::Swapchain::getSwapchain() noexcept
{
    return swapchain;
}

const VkExtent2D& UVK::Swapchain::getExtent() const noexcept
{
    return extent;
}

void UVK::Swapchain::setDepthBuffer(UVK::VKDepthBuffer& depth) noexcept
{
    depthBuffer = &depth;
}

void UVK::Swapchain::createMultisampledImage() noexcept
{
    colourImage.createImage({ extent.width, extent.height }, surfaceFormat.format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, *device, 1, static_cast<VkSampleCountFlagBits>(global.rendererSettings.samples));
    colourImage.createImageView(surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT, *device);
}

void UVK::Swapchain::destroyMultisampledImage() noexcept
{
    colourImage.destroy(*device);
}
