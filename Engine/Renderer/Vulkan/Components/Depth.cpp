#include "Depth.hpp"
#include <Core/Interfaces/RendererInterface.hpp>

void UVK::VKDepthBuffer::createDepthBufferImage(const Swapchain& swapchain, VKDevice& device) noexcept
{
    depthFormat = SwapchainImage::findBestImageFormat({ VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT }, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT, device);
    depthImage.createImage({ swapchain.getExtent().width, swapchain.getExtent().height }, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, device, 1, static_cast<VkSampleCountFlagBits>(Renderer::msaaSampleCount()));
    depthImage.createImageView(depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, device);
}

void UVK::VKDepthBuffer::destroyDepthBufferImage(VKDevice& device) noexcept
{
    depthImage.destroy(device);
}

VkFormat& UVK::VKDepthBuffer::getFormat() noexcept
{
    return depthFormat;
}

UVK::SwapchainImage& UVK::VKDepthBuffer::getImage() noexcept
{
    return depthImage;
}
