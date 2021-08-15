// VKFramebuffer.hpp
// Last update 2/7/2021 by Madman10K
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

        void init(VkImageView& imageView, const VkRenderPass& renderPass, FVector2 windowSize, VKDevice* dev);
        void use();
        void destroy();
        Texture getTexture();
    private:
        VKDevice* device;

        friend class VKSwapchain;
        VkFramebuffer framebuffer;
    };
}
