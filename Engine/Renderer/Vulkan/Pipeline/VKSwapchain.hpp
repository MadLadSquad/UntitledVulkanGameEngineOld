// VKSwapchain.hpp
// Last update 16/8/2021 by Madman10K
#pragma once
#ifndef __APPLE__
#include <vulkan/vulkan.h>
#include "../Components/VKStructs.hpp"
#include "VKInstance.hpp"
#include <Renderer/Vulkan/Components/VKFramebuffer.hpp>

namespace UVK
{
    class Device;
    class VKFramebuffer;
    struct VKSwapchainImage;

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
        friend class VKDraw;
        friend class VKDescriptorSets;

        void set(VKInstance* inst, Device* dev);
        void addRenderPassPointer(VkRenderPass* rp, VkPipeline* gp);

        void createSurface();
        void destroySurface();

        void createSwapchain(VkSwapchainKHR destroyedSwapchain);
        void destroySwapchain();

        void createFramebuffers();
        void destroyFramebuffers();

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
        VkSwapchainKHR swapchain = VK_NULL_HANDLE;

        VkRenderPass* renderPass;

        VKInstance* instance;
        Device* device;
        VkPipeline* graphicsPipeline;

        std::vector<VKSwapchainImage> images;
        std::vector<VKFramebuffer> framebuffers;
    };
}
#endif
