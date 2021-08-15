// VKGraphicsPipeline.hpp
// Last update 12/8/2021 by Madman10K
#pragma once
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

namespace UVK
{
    class VKDevice;
    class VKSwapchain;

    /**
     * @brief A Vulkan graphics pipeline manager
     */
    class VKGraphicsPipeline
    {
    public:
        VKGraphicsPipeline() = default;
        VKGraphicsPipeline(VKDevice* dev, VKSwapchain* swap);

        void create();
        void destroy();

        VkPipeline& data();
        VkRenderPass& getRenderPass();
    private:
        VKSwapchain* swapchain;
        VKDevice* device;

        VkPipelineLayout layout;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;

        void createShaderStage(const VkShaderModule& vertexModule, const VkShaderModule& fragmentModule);
        void createViewportAndPipeline(VkPipelineShaderStageCreateInfo* shaderStages, const VkPipelineInputAssemblyStateCreateInfo& inputAssembly, VkPipelineVertexInputStateCreateInfo& vertexInputStateCreateInfo);
        void createRenderPass();

        void createPipelineLayout(VkViewport& viewport, VkRect2D& scissor, VkPipelineRasterizationStateCreateInfo& rasterizationStateCreateInfo, VkPipelineViewportStateCreateInfo& viewportStateCreateInfo, VkPipelineMultisampleStateCreateInfo& multisampleStateCreateInfo, VkPipelineColorBlendAttachmentState& colourState, VkPipelineColorBlendStateCreateInfo& colourBlendingCreateInfo, VkPipelineLayoutCreateInfo& pipelineLayoutCreateInfo);
        void createPipeline(VkPipelineShaderStageCreateInfo* shaderStages, const VkPipelineInputAssemblyStateCreateInfo& inputAssembly, VkPipelineVertexInputStateCreateInfo& vertexInputStateCreateInfo, const VkPipelineViewportStateCreateInfo& viewportStateCreateInfo, const VkPipelineRasterizationStateCreateInfo& rasterizationStateCreateInfo, const VkPipelineMultisampleStateCreateInfo& multisampleStateCreateInfo, const VkPipelineColorBlendStateCreateInfo& colourBlendingCreateInfo);
    };
}