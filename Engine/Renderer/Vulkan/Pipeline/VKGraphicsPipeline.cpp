// VKGraphicsPipeline.cpp
// Last update 12/8/2021 by Madman10K
#include <GL/glew.h>
#include "VKGraphicsPipeline.hpp"
#include "Renderer/Vulkan/Components/VKShader.hpp"
#include <Core/Global.hpp>
#include <Renderer/Vulkan/Components/VKStructs.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

void UVK::VKGraphicsPipeline::create()
{
    auto vert = VKShader(device);
    auto frag = VKShader(device);

    vert.createShader("shader.vert");
    frag.createShader("shader.frag");

    createShaderStage(vert.shaderModule, frag.shaderModule);

    vert.destroyShaderModule();
    frag.destroyShaderModule();
}

void UVK::VKGraphicsPipeline::destroy()
{
    vkDestroyPipelineLayout(device->logicalDevice, layout, nullptr);
}

void UVK::VKGraphicsPipeline::createShaderStage(VkShaderModule& vertexModule, VkShaderModule& fragmentModule)
{
    VkPipelineShaderStageCreateInfo shaderStages[2];

    shaderStages[VK_SHADER_STAGE_VERT] = {};
    shaderStages[VK_SHADER_STAGE_VERT].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[VK_SHADER_STAGE_VERT].module = vertexModule;
    shaderStages[VK_SHADER_STAGE_VERT].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[VK_SHADER_STAGE_VERT].pName = "main";

    shaderStages[VK_SHADER_STAGE_FRAG] = {};
    shaderStages[VK_SHADER_STAGE_FRAG].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[VK_SHADER_STAGE_FRAG].module = fragmentModule;
    shaderStages[VK_SHADER_STAGE_FRAG].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[VK_SHADER_STAGE_FRAG].pName = "main";

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
    vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateCreateInfo.vertexBindingDescriptionCount = 0;
    vertexInputStateCreateInfo.vertexAttributeDescriptionCount = 0;
    vertexInputStateCreateInfo.pVertexBindingDescriptions = nullptr;
    vertexInputStateCreateInfo.pVertexAttributeDescriptions = nullptr;

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    createViewport();
}

UVK::VKGraphicsPipeline::VKGraphicsPipeline(UVK::VKDevice* dev)
{
    device = dev;
}

void UVK::VKGraphicsPipeline::createViewport()
{
    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)Window::windowSize().x;
    viewport.height = (float)Window::windowSize().y;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = { (uint32_t)Window::windowSize().x, (uint32_t)Window::windowSize().y };

    VkPipelineViewportStateCreateInfo viewportStateCreateInfo = {};
    viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateCreateInfo.viewportCount = 1;
    viewportStateCreateInfo.pViewports = &viewport;
    viewportStateCreateInfo.scissorCount = 1;
    viewportStateCreateInfo.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
    rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
    rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationStateCreateInfo.lineWidth = 1.0f;
    rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;

    // TODO: Implement multisampling
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
    multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
    multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // TODO: Blending
    VkPipelineColorBlendAttachmentState colourState = {};
    colourState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colourState.blendEnable = VK_TRUE;
    colourState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colourState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colourState.colorBlendOp = VK_BLEND_OP_ADD;
    colourState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colourState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    colourState.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colourBlendingCreateInfo = {};
    colourBlendingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colourBlendingCreateInfo.logicOpEnable = VK_FALSE;
    colourBlendingCreateInfo.attachmentCount = 1;
    colourBlendingCreateInfo.pAttachments = &colourState;

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
    pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutCreateInfo.setLayoutCount = 0;
    pipelineLayoutCreateInfo.pSetLayouts = nullptr;
    pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
    pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

    auto result = vkCreatePipelineLayout(device->logicalDevice, &pipelineLayoutCreateInfo, nullptr, &layout);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Creation of Vulkan graphics pipeline failed", UVK_LOG_TYPE_ERROR);
    }


}