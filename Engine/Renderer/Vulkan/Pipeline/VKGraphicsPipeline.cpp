// VKGraphicsPipeline.cpp
// Last update 12/8/2021 by Madman10K
#include <GL/glew.h>
#include "VKGraphicsPipeline.hpp"
#include "Renderer/Vulkan/Components/VKShader.hpp"
#include <Core/Global.hpp>
#include <Renderer/Vulkan/Components/VKStructs.hpp>
#include <Renderer/Vulkan/Pipeline/VKSwapchain.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

void UVK::VKGraphicsPipeline::create()
{
    createRenderPass();

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
    vkDestroyPipeline(device->logicalDevice, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device->logicalDevice, layout, nullptr);
    vkDestroyRenderPass(device->logicalDevice, renderPass, nullptr);
}

void UVK::VKGraphicsPipeline::createShaderStage(const VkShaderModule& vertexModule, const VkShaderModule& fragmentModule)
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

    createViewportAndPipeline(shaderStages, inputAssembly, vertexInputStateCreateInfo);
}

UVK::VKGraphicsPipeline::VKGraphicsPipeline(UVK::VKDevice* dev, VKSwapchain* swap)
{
    device = dev;
    swapchain = swap;
}

void UVK::VKGraphicsPipeline::createViewportAndPipeline(VkPipelineShaderStageCreateInfo* shaderStages, const VkPipelineInputAssemblyStateCreateInfo& inputAssembly, VkPipelineVertexInputStateCreateInfo& vertexInputStateCreateInfo)
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

    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
    VkPipelineViewportStateCreateInfo viewportStateCreateInfo = {};
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
    VkPipelineColorBlendAttachmentState colourState = {};
    VkPipelineColorBlendStateCreateInfo colourBlendingCreateInfo = {};
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};

    createPipelineLayout(viewport, scissor, rasterizationStateCreateInfo, viewportStateCreateInfo, multisampleStateCreateInfo, colourState, colourBlendingCreateInfo, pipelineLayoutCreateInfo);
    createPipeline(shaderStages, inputAssembly, vertexInputStateCreateInfo, viewportStateCreateInfo, rasterizationStateCreateInfo, multisampleStateCreateInfo, colourBlendingCreateInfo);
}

void UVK::VKGraphicsPipeline::createPipelineLayout(VkViewport& viewport, VkRect2D& scissor, VkPipelineRasterizationStateCreateInfo& rasterizationStateCreateInfo, VkPipelineViewportStateCreateInfo& viewportStateCreateInfo, VkPipelineMultisampleStateCreateInfo& multisampleStateCreateInfo, VkPipelineColorBlendAttachmentState& colourState, VkPipelineColorBlendStateCreateInfo& colourBlendingCreateInfo, VkPipelineLayoutCreateInfo& pipelineLayoutCreateInfo)
{
    viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateCreateInfo.viewportCount = 1;
    viewportStateCreateInfo.pViewports = &viewport;
    viewportStateCreateInfo.scissorCount = 1;
    viewportStateCreateInfo.pScissors = &scissor;

    rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
    rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationStateCreateInfo.lineWidth = 1.0f;
    rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;

    // TODO: Implement multisampling
    multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
    multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // TODO: Blending
    colourState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colourState.blendEnable = VK_TRUE;
    colourState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colourState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colourState.colorBlendOp = VK_BLEND_OP_ADD;
    colourState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colourState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colourState.alphaBlendOp = VK_BLEND_OP_ADD;

    colourBlendingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colourBlendingCreateInfo.logicOpEnable = VK_FALSE;
    colourBlendingCreateInfo.attachmentCount = 1;
    colourBlendingCreateInfo.pAttachments = &colourState;

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

    // TODO: Add depth stencil
}

void UVK::VKGraphicsPipeline::createRenderPass()
{
    VkAttachmentDescription colourAttachment = {};
    colourAttachment.format = swapchain->swapchainFormat;
    colourAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colourAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colourAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colourAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colourAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colourAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colourAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;    

    VkAttachmentReference colourAttachmentReference = {};
    colourAttachmentReference.attachment = 0;
    colourAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colourAttachmentReference;

    VkSubpassDependency subpassDependencies[2];
    subpassDependencies[VK_UNDEFINED_TO_SUBPASS_LAYOUT].srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[VK_UNDEFINED_TO_SUBPASS_LAYOUT].dstSubpass = 1;
    subpassDependencies[VK_UNDEFINED_TO_SUBPASS_LAYOUT].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    subpassDependencies[VK_UNDEFINED_TO_SUBPASS_LAYOUT].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[VK_UNDEFINED_TO_SUBPASS_LAYOUT].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    subpassDependencies[VK_UNDEFINED_TO_SUBPASS_LAYOUT].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[VK_UNDEFINED_TO_SUBPASS_LAYOUT].dependencyFlags = 0;

    subpassDependencies[VK_SUBPASS_TO_PRESENTATION_LAYOUT].srcSubpass = 0;
    subpassDependencies[VK_SUBPASS_TO_PRESENTATION_LAYOUT].dstSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[VK_SUBPASS_TO_PRESENTATION_LAYOUT].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[VK_SUBPASS_TO_PRESENTATION_LAYOUT].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    subpassDependencies[VK_SUBPASS_TO_PRESENTATION_LAYOUT].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[VK_SUBPASS_TO_PRESENTATION_LAYOUT].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    subpassDependencies[VK_SUBPASS_TO_PRESENTATION_LAYOUT].dependencyFlags = 0;

    VkRenderPassCreateInfo renderPassCreateInfo = {};
    renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.attachmentCount = 1;
    renderPassCreateInfo.pAttachments = &colourAttachment;
    renderPassCreateInfo.subpassCount = 1;
    renderPassCreateInfo.pSubpasses = &subpass;
    renderPassCreateInfo.dependencyCount = 2;
    renderPassCreateInfo.pDependencies = subpassDependencies;

    auto result = vkCreateRenderPass(device->logicalDevice, &renderPassCreateInfo, nullptr, &renderPass);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan Render Pass!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}

void UVK::VKGraphicsPipeline::createPipeline(VkPipelineShaderStageCreateInfo* shaderStages, const VkPipelineInputAssemblyStateCreateInfo& inputAssembly, VkPipelineVertexInputStateCreateInfo& vertexInputStateCreateInfo, const VkPipelineViewportStateCreateInfo& viewportStateCreateInfo, const VkPipelineRasterizationStateCreateInfo& rasterizationStateCreateInfo, const VkPipelineMultisampleStateCreateInfo& multisampleStateCreateInfo, const VkPipelineColorBlendStateCreateInfo& colourBlendingCreateInfo)
{
    VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
    pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineCreateInfo.stageCount = 2;
    pipelineCreateInfo.pStages = shaderStages;
    pipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
    pipelineCreateInfo.pInputAssemblyState = &inputAssembly;
    pipelineCreateInfo.pViewportState = &viewportStateCreateInfo;
    pipelineCreateInfo.pDynamicState = nullptr;
    pipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
    pipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
    pipelineCreateInfo.pColorBlendState = &colourBlendingCreateInfo;
    pipelineCreateInfo.pDepthStencilState = nullptr;
    pipelineCreateInfo.layout = layout;
    pipelineCreateInfo.renderPass = renderPass;
    pipelineCreateInfo.subpass = 0;
    pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineCreateInfo.basePipelineIndex = -1;

    auto result = vkCreateGraphicsPipelines(device->logicalDevice, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &graphicsPipeline);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan Graphics Pipeline!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}
