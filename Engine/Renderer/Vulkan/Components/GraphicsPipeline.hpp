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
        GraphicsPipeline(VKDevice& dev, Swapchain& swap, VKDescriptors& desc, VKDepthBuffer& depth) noexcept;
        ~GraphicsPipeline() = default;

        void createGraphicsPipeline() noexcept;
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