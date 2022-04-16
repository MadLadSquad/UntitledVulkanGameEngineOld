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
        //void createCommandPool() noexcept;
        //void destroyCommandPool() noexcept;
//
        //void createCommandBuffers() noexcept;
        //void destroyCommandBuffers() noexcept;

        //void createSynchronisation() noexcept;
        //void destroySynchronisation() noexcept;

        //void createUniformBuffers() noexcept;
        //void updateUniformBuffers(VP& mvp, uint32_t imageIndex, std::vector<VKMesh>& meshes) noexcept;
        //void destroyUniformBuffers() noexcept;

        //void recordCommands(uint32_t currentImage, std::vector<VKMesh>& meshes) noexcept;
        //void draw(VP& mvp, std::vector<VKMesh>& meshes) noexcept;

        //void allocateDynamicUniformBufferTransferSpace();
        //void freeDynamicUniformBufferTransferSpace();


        VkSurfaceKHR& getSurface() noexcept;
        VkSwapchainKHR& getSwapchain() noexcept;
        //VkCommandPool& getCommandPool() noexcept;
        [[nodiscard]] const VkExtent2D& getExtent() const noexcept;
        [[nodiscard]] const std::vector<VkFramebuffer>& getFramebuffers() const noexcept;
        //Commands& getCommands() noexcept;
        //VKResources& getResources() noexcept;
        static VkImageView createImageView(const VkImage& image, const VkFormat& format, const VkImageAspectFlags& aspectFlags, VKDevice& dev, uint32_t mipLevels = 1) noexcept;
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

        //VKResources resources{};
        //Commands commands{};

        //VkCommandPool commandPool{};

        //Model* modelTransferSpace = nullptr;
        //VkDeviceSize modelUniformAlignment = 0;

        //std::vector<VkSemaphore> imageAvailable;
        //std::vector<VkSemaphore> renderFinished;
        //std::vector<VkFence> fences;

        std::vector<SwapchainImage> images;
        std::vector<VkFramebuffer> framebuffers;
        //std::vector<VkCommandBuffer> commandBuffers;
        //std::vector<VKBuffer> uniformBuffers;
        //std::vector<VKBuffer> dynamicUniformBuffers;
    };
}