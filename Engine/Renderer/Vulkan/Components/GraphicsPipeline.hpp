#pragma once
#include "Device.hpp"

namespace UVK
{
    class GraphicsPipeline
    {
    public:
        GraphicsPipeline() = default;
        GraphicsPipeline(VKDevice& dev, Swapchain& swap);
        ~GraphicsPipeline();

        void createGraphicsPipeline();
        void createRenderPass();
        void destroyGraphicsPipeline();
    private:
        VKDevice* device = nullptr;
        Swapchain* swapchain = nullptr;

        VkPipelineLayout pipelineLayout;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;
    };
}