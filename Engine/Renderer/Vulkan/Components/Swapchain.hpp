#pragma once
#include "Instance.hpp"
#include "Utility.hpp"
#include "Device.hpp"
#include "VKMesh.hpp"

namespace UVK
{
    class GraphicsPipeline;
    class Swapchain
    {
    public:
        Swapchain() = default;
        Swapchain(VKInstance& inst, VKDevice& dev) noexcept;
        ~Swapchain() noexcept;

        void createSwapchain() noexcept;
        void destroySwapchain() noexcept;

        void createSurface() noexcept;
        void destroySurface() noexcept;

        void createFramebuffers(GraphicsPipeline& graphicsPipeline) noexcept;
        void destroyFramebuffers() noexcept;

        void createCommandPool() noexcept;
        void destroyCommandPool() noexcept;

        void createCommandBuffers() noexcept;
        void destroyCommandBuffers() noexcept;

        void createSynchronisation() noexcept;
        void destroySynchronisation() noexcept;

        void recordCommands(std::vector<VKMesh>& meshes) noexcept;
        void draw() noexcept;

        VkSurfaceKHR& getSurface() noexcept;
    private:
        friend class VKDevice;
        friend class GraphicsPipeline;

        bool getSwapchainDetails(VkPhysicalDevice& device, const QueueFamilyIndices& indices) noexcept;

        VkImageView createImageView(const VkImage& image, const VkFormat& format, const VkImageAspectFlags& aspectFlags) noexcept;

        void determineSurfaceFormats() noexcept;
        void determinePresentationMode() noexcept;
        void determineExtent() noexcept;

        SwapchainDetails details;
        VkSurfaceKHR surface{};
        VkSwapchainKHR swapchain{};

        VKInstance* instance = nullptr;
        VKDevice* device = nullptr;
        GraphicsPipeline* pipeline = nullptr;

        VkSurfaceFormatKHR surfaceFormat{};
        VkPresentModeKHR presentationMode{};
        VkExtent2D extent{};

        VkCommandPool commandPool{};

        std::vector<VkSemaphore> imageAvailable;
        std::vector<VkSemaphore> renderFinished;
        std::vector<VkFence> fences;

        std::vector<SwapchainImage> images;
        std::vector<VkFramebuffer> framebuffers;
        std::vector<VkCommandBuffer> commandBuffers;
    };
}