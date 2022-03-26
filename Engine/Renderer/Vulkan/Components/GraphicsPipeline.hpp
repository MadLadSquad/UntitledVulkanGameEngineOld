#pragma once
#include "Device.hpp"

namespace UVK
{
    class GraphicsPipeline
    {
    public:
        GraphicsPipeline() = default;
        GraphicsPipeline(VKDevice& dev, Swapchain& swap) noexcept;
        ~GraphicsPipeline() noexcept;

        void createGraphicsPipeline() noexcept;
        void createRenderPass() noexcept;
        void destroyGraphicsPipeline() noexcept;
    private:
        friend class Swapchain;

        VKDevice* device = nullptr;
        Swapchain* swapchain = nullptr;

        VkPipelineLayout pipelineLayout{};
        VkRenderPass renderPass{};
        VkPipeline graphicsPipeline{};
    };
}