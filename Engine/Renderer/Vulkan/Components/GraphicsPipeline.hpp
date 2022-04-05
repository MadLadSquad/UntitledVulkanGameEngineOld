#pragma once
#include "Device.hpp"
#include "Descriptors.hpp"

namespace UVK
{
    class GraphicsPipeline
    {
    public:
        GraphicsPipeline() = default;
        GraphicsPipeline(VKDevice& dev, Swapchain& swap, const VKDescriptors& desc) noexcept;
        ~GraphicsPipeline() noexcept;

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
        const VKDescriptors* descriptors = nullptr;

        VkPipelineLayout pipelineLayout{};
        VkRenderPass renderPass{};
        VkPipeline graphicsPipeline{};
    };
}