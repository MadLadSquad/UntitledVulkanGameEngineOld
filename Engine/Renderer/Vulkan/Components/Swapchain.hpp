#pragma once
#include "Instance.hpp"
#include "Utility.hpp"
#include "Device.hpp"
#include "VKMesh.hpp"
#include "Descriptors.hpp"
#include "Resources.hpp"
#include "Commands.hpp"

namespace UVK
{
    class GraphicsPipeline;
    class Swapchain
    {
    public:
        Swapchain() = default;
        Swapchain(VKInstance& inst, VKDevice& dev) noexcept;
        ~Swapchain() = default;

        void createSwapchain(VkSwapchainKHR oldswapchain = VK_NULL_HANDLE) noexcept;
        void destroySwapchain(bool bNoDestroy = false) noexcept;

        void createSurface() noexcept;
        void destroySurface() noexcept;

        void createFramebuffers(GraphicsPipeline& graphicsPipeline) noexcept;
        void destroyFramebuffers() noexcept;

        void setDepthBuffer(VKDepthBuffer& depth) noexcept;

        void createMultisampledImage() noexcept;
        void destroyMultisampledImage() noexcept;

        VkSurfaceKHR& getSurface() noexcept;
        VkSwapchainKHR& getSwapchain() noexcept;
        [[nodiscard]] const VkExtent2D& getExtent() const noexcept;
        [[nodiscard]] const std::vector<VkFramebuffer>& getFramebuffers() const noexcept;
    private:
        friend class VKDevice;
        friend class GraphicsPipeline;
        friend class VKDescriptors;

        bool getSwapchainDetails(VkPhysicalDevice& device, const QueueFamilyIndices& indices) noexcept;

        void determineSurfaceFormats() noexcept;
        void determinePresentationMode() noexcept;
        void determineExtent() noexcept;

        SwapchainDetails details;
        VkSurfaceKHR surface{};
        VkSwapchainKHR swapchain{};

        VKInstance* instance = nullptr;
        VKDevice* device = nullptr;
        GraphicsPipeline* pipeline = nullptr;
        VKDescriptors* descriptors = nullptr;
        VKDepthBuffer* depthBuffer = nullptr;

        VkSurfaceFormatKHR surfaceFormat{};
        VkPresentModeKHR presentationMode{};
        VkExtent2D extent{};

        std::vector<SwapchainImage> images;
        std::vector<VkFramebuffer> framebuffers;

        SwapchainImage colourImage{};
    };
}