// VKFramebuffer.cpp
// Last update 2/7/2021 by Madman10K
#include "VKFramebuffer.hpp"
#include "VKStructs.hpp"

void UVK::VKFramebuffer::init(VkImageView& imageView, const VkRenderPass& renderPass, FVector2 windowSize, VKDevice* dev)
{
    device = dev;
    VkImageView attachments[1] = { imageView };

    VkFramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.renderPass = renderPass;
    framebufferCreateInfo.attachmentCount = 1;
    framebufferCreateInfo.pAttachments = attachments;
    framebufferCreateInfo.width = windowSize.x;
    framebufferCreateInfo.height = windowSize.y;
    framebufferCreateInfo.layers = 1;

    auto result = vkCreateFramebuffer(device->logicalDevice, &framebufferCreateInfo, nullptr, &framebuffer);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Cannot create Vulkan Framebuffer!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}

void UVK::VKFramebuffer::use()
{

}

void UVK::VKFramebuffer::destroy()
{
    vkDestroyFramebuffer(device->logicalDevice, framebuffer, nullptr);
}

UVK::Texture UVK::VKFramebuffer::getTexture()
{
    return UVK::Texture();
}
