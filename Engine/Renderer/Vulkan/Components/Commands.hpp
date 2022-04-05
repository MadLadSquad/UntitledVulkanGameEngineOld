#pragma once
#include "Device.hpp"
#include "GraphicsPipeline.hpp"
#include "Resources.hpp"

namespace UVK
{
    class Commands
    {
    public:
        Commands() = default;
        Commands(VKDevice& dev, Swapchain& swap, GraphicsPipeline& graphicsPipeline, VKDescriptors& desc, VKResources& res);

        void createCommandPool() noexcept;
        void destroyCommandPool() noexcept;
        VkCommandPool& getCommandPool() noexcept;

        void createCommandBuffers(size_t dependencySizeLink) noexcept;
        void destroyCommandBuffers() noexcept;
        [[nodiscard]] const std::vector<VkCommandBuffer>& getCommandBuffers() const noexcept;

        void createSynchronization() noexcept;
        void destroySynchronization() noexcept;

        void draw() noexcept;
        void recordCommands(uint32_t currentImage) noexcept;
    private:
        VKDevice* device = nullptr;
        Swapchain* swapchain = nullptr;
        GraphicsPipeline* pipeline = nullptr;
        VKDescriptors* descriptors = nullptr;
        VKResources* resources = nullptr;

        VkCommandPool commandPool{};
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailable;
        std::vector<VkSemaphore> renderFinished;
        std::vector<VkFence> fences;
    };
}