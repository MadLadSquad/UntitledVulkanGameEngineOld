// VKSwapchain.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#ifndef __APPLE__
#include <vulkan/vulkan.h>
#include "../Components/VKStructs.hpp"
#include "VKInstance.hpp"
#include <Renderer/Vulkan/Components/VKFramebuffer.hpp>
#include <Renderer/Vulkan/Components/VKCommandBuffer.hpp>

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
        void addRenderPassPointer(VkRenderPass* rp, VkPipeline* gp);

        void createSurface();
        void destroySurface();

        void createSwapchain();
        void destroySwapchain();

        void createCommandPool();
        void destroyCommandPool();

        void createFramebuffers();
        void destroyFramebuffers();

        void createCommandbuffers();

        void recordCommands();

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

        VkRenderPass* renderPass;

        VkCommandPool commandPool;

        VKInstance* instance;
        Device* device;
        VkPipeline* graphicsPipeline;

        std::vector<VKSwapchainImage> images;
        std::vector<VKFramebuffer> framebuffers;
        std::vector<VkCommandBuffer> commandbuffers;
    };
}
#endif
