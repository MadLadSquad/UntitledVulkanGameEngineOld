// Swapchain.hpp
// Last update 26/02/2022 by Madman10K
#pragma once
#include "Instance.hpp"
#include "Utility.hpp"
#include "Device.hpp"

namespace UVK
{
    class GraphicsPipeline;
    class Swapchain
    {
    public:
        Swapchain() = default;
        Swapchain(VKInstance& inst, VKDevice& dev);
        ~Swapchain();

        void createSwapchain();
        void destroySwapchain();

        void createSurface();
        void destroySurface();

        void createFramebuffers(GraphicsPipeline& graphicsPipeline);
        void destroyFramebuffers();

        void createCommandPool();
        void destroyCommandPool();

        void createCommandBuffers();
        void destroyCommandBuffers();

        void createSynchronisation();
        void destroySynchronisation();

        void recordCommands();
        void draw();

        VkSurfaceKHR& getSurface();
    private:
        friend class VKDevice;
        friend class GraphicsPipeline;

        bool getSwapchainDetails(VkPhysicalDevice& device, const QueueFamilyIndices& indices);

        VkImageView createImageView(const VkImage& image, const VkFormat& format, const VkImageAspectFlags& aspectFlags);

        void determineSurfaceFormats();
        void determinePresentationMode();
        void determineExtent();

        SwapchainDetails details;
        VkSurfaceKHR surface{};
        VkSwapchainKHR swapchain{};

        VKInstance* instance = nullptr;
        VKDevice* device = nullptr;
        GraphicsPipeline* pipeline = nullptr;

        VkSurfaceFormatKHR surfaceFormat{};
        VkPresentModeKHR presentationMode{};
        VkExtent2D extent{};

        VkCommandPool commandPool;

        std::vector<VkSemaphore> imageAvailable;
        std::vector<VkSemaphore> renderFinished;
        std::vector<VkFence> fences;

        std::vector<SwapchainImage> images;
        std::vector<VkFramebuffer> framebuffers;
        std::vector<VkCommandBuffer> commandBuffers;
    };
}