// VKFramebuffer.hpp
// Last update 16/8/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif
#include "../../Textures/Texture.hpp"

namespace UVK
{
    class VKDevice;

    /**
     * @brief Vulkan specific framebuffer class
     */
    class VKFramebuffer
    {
    public:
        VKFramebuffer() = default;

        void init(const VkImageView& imageView, const VkRenderPass& renderPass, FVector2 windowSize, VKDevice* dev);
        void use();
        void destroy();
        Texture getTexture();
    private:
        VKDevice* device;

        friend class VKSwapchain;
        friend class VKCommandBuffers;
        VkFramebuffer framebuffer;
    };
}
