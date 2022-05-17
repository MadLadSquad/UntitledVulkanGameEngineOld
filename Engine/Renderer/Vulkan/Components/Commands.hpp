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
        /**
         * @brief Initializes the Commands class
         * @param dev - The Vulkan device abstraction class
         * @param swap - The Swapchain abstraction class
         * @param graphicsPipeline - The graphics pipeline abstraction class
         * @param desc - The Vulkan Descriptors abstraction class
         * @param res - The Vulkan resources abstraction class
         */
        Commands(VKDevice& dev, Swapchain& swap, GraphicsPipeline& graphicsPipeline, VKDescriptors& desc, VKResources& res);

        // Allocates the command pool
        void createCommandPool() noexcept;
        void destroyCommandPool() noexcept;
        VkCommandPool& getCommandPool() noexcept;

        /**
         * @brief Creates the command buffers to be used
         * @param dependencySizeLink - The size of the framebuffer array? Basically we sync the sizes of a couple of arrays and this variable makes sure the size is 1:1
         */
        void createCommandBuffers(size_t dependencySizeLink) noexcept;
        void destroyCommandBuffers() noexcept;
        [[nodiscard]] const std::vector<VkCommandBuffer>& getCommandBuffers() const noexcept;

        /**
         * @brief Creates the synchronisation structs, which are the Semaphores and fences
         */
        void createSynchronization() noexcept;
        void destroySynchronization() noexcept;

        /**
         * @brief Draws an image to the screen
         */
        void draw() noexcept;
        /**
         * @brief Records the commands for drawing an image to the screen
         * @param currentImage
         */
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