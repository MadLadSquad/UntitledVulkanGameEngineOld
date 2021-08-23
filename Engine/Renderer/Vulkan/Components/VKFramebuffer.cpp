// VKFramebuffer.cpp
// Last update 16/8/2021 by Madman10K
#include "VKFramebuffer.hpp"
#include "VKStructs.hpp"
#include "UVKLog.h"

void UVK::VKFramebuffer::init(const VkImageView& imageView, const VkRenderPass& renderPass, FVector2 windowSize, VKDevice* dev)
{
    device = dev;
    VkImageView attachments[1] = { imageView };

    const VkFramebufferCreateInfo framebufferCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = renderPass,
        .attachmentCount = 1,
        .pAttachments = attachments,
        .width = static_cast<uint32_t>(windowSize.x),
        .height = static_cast<uint32_t>(windowSize.y),
        .layers = 1
    };

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
