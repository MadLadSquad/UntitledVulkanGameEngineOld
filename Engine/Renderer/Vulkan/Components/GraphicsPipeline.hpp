#pragma once
#include "Device.hpp"
#include "Descriptors.hpp"

namespace UVK
{
    class VKDepthBuffer;
    class GraphicsPipeline
    {
    public:
        GraphicsPipeline() = default;
        /**
         * @brief Initialize the graphics pipeline
         * @param dev - The device to be used
         * @param swap - The swapchain to be used
         * @param desc - The descriptor sets to be used
         * @param depth - The depth buffer to be used
         */
        GraphicsPipeline(VKDevice& dev, Swapchain& swap, VKDescriptors& desc, VKDepthBuffer& depth) noexcept;
        ~GraphicsPipeline() = default;

        // Creates the graphics pipeline and shader modules
        void createGraphicsPipeline() noexcept;
        // Creates the render and sub passes
        void createRenderPass() noexcept;
        void destroyGraphicsPipeline() noexcept;

        VkPipelineLayout& getPipelineLayout() noexcept;
        VkRenderPass& getRenderPass() noexcept;
        VkPipeline& getPipeline() noexcept;
    private:
        friend class Swapchain;

        VKDevice* device = nullptr;
        Swapchain* swapchain = nullptr;
        VKDescriptors* descriptors = nullptr;

        VKDepthBuffer* depthBuffer = nullptr;
        VkPipelineLayout pipelineLayout{};
        VkRenderPass renderPass{};
        VkPipeline graphicsPipeline{};
    };
}