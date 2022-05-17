#pragma once
#include "Utility.hpp"
#include "Swapchain.hpp"

namespace UVK
{
    class VKDepthBuffer
    {
    public:
        /**
         * @brief Creates a depth buffer image
         * @param swapchain - A reference to the current swapchain abstraction struct
         * @param device - A reference to the device abstraction struct
         */
        void createDepthBufferImage(const Swapchain& swapchain, VKDevice& device) noexcept;
        void destroyDepthBufferImage(VKDevice& device) noexcept;

        /**
         * @return The image format for the depth buffer image
         */
        VkFormat& getFormat() noexcept;
        /**
         * @return The actual depth buffer image
         */
        SwapchainImage& getImage() noexcept;
    private:
        SwapchainImage depthImage{};
        VkDeviceMemory bufferImageMemory{};
        VkFormat depthFormat{};
    };
}