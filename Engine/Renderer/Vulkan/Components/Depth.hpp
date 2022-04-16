#pragma once
#include "Utility.hpp"
#include "Swapchain.hpp"

namespace UVK
{
    class VKDepthBuffer
    {
    public:
        void createDepthBufferImage(const Swapchain& swapchain, VKDevice& device) noexcept;
        void destroyDepthBufferImage(VKDevice& device) noexcept;

        VkFormat& getFormat() noexcept;
        SwapchainImage& getImage() noexcept;
    private:
        SwapchainImage depthImage{};
        VkDeviceMemory bufferImageMemory{};
        VkFormat depthFormat{};
    };
}