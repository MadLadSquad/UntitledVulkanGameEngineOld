// VKSwapchain.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#ifndef __APPLE__
    #include <vulkan/vulkan.h>

#include "../Components/VKStructs.hpp"
#include "VKInstance.hpp"

namespace UVK
{
    class Device;

    /**
     * @brief Manages a Vulkan swapchain
     */
    class VKSwapchain
    {
    public:
        VKSwapchain() = default;
    private:
        friend class VKPipeline;
        friend class VKGraphicsPipeline;
        friend class Device;

        void set(VKInstance* inst, Device* dev);

        void createSurface();
        void destroySurface();

        void createSwapchain();
        void destroySwapchain();

        VKSwapchainSettings getSwapchainSettings();

        VkSurfaceKHR& getSurface()
        {
            return surface;
        }
        static VkSurfaceFormatKHR findSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
        static VkPresentModeKHR findPresentationMode(const std::vector<VkPresentModeKHR>& modes);
        static VkExtent2D findSwapchainExtent(const VkSurfaceCapabilitiesKHR& surfaceCapabilities);
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

        VkSurfaceKHR surface;
        VkFormat swapchainFormat;
        VkExtent2D swapchainExtent;
        VkSwapchainKHR swapchain;

        VKInstance* instance;
        Device* device;

        std::vector<VKSwapchainImage> images;
    };
}
#endif
