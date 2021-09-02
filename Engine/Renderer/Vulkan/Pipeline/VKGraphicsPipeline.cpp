// VKGraphicsPipeline.cpp
// Last update 2/9/2021 by Madman10K
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

VkPipeline& UVK::VKGraphicsPipeline::data()
{
    return graphicsPipeline;
}

VkRenderPass& UVK::VKGraphicsPipeline::getRenderPass()
{
    return renderPass;
}

void UVK::VKGraphicsPipeline::createShaderStage(const VkShaderModule& vertexModule, const VkShaderModule& fragmentModule)
{
    VkPipelineShaderStageCreateInfo shaderStages[2] =
    {
        {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_VERTEX_BIT,
            .module = vertexModule,
            .pName = "main"
        },
        {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = fragmentModule,
            .pName = "main"
        }
    };

    constexpr VkVertexInputBindingDescription vertexInputBindingDescription =
    {
        .binding = 0,
        .stride = sizeof(VKVertex), // set the stride to the size of a 4D vector
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
    };

    const VkVertexInputAttributeDescription attributeDescriptions[2] =
    {
        {
            .location = 0,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32A32_SFLOAT, // If given a Vector3, it will render all the stuff on half of the screen. And btw TODO: look at this place if something breaks
            .offset = offsetof(VKVertex, loc),
        },
        {
            .location = 1,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32A32_SFLOAT, // If given a Vector3, it will render all the stuff on half of the screen. And btw TODO: look at this place if something breaks
            .offset = offsetof(VKVertex, colour)
        }
    };

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &vertexInputBindingDescription,
        .vertexAttributeDescriptionCount = 2,
        .pVertexAttributeDescriptions = attributeDescriptions
    };

    constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE,
    };

    createViewportAndPipeline(shaderStages, inputAssembly, vertexInputStateCreateInfo);
}

UVK::VKGraphicsPipeline::VKGraphicsPipeline(UVK::VKDevice* dev, VKSwapchain* swap, VkDescriptorSetLayout* descriptorSetL)
{
    device = dev;
    swapchain = swap;
    descriptorSetLayout = descriptorSetL;
}

void UVK::VKGraphicsPipeline::createViewportAndPipeline(VkPipelineShaderStageCreateInfo* shaderStages, const VkPipelineInputAssemblyStateCreateInfo& inputAssembly, VkPipelineVertexInputStateCreateInfo& vertexInputStateCreateInfo)
{
    VkViewport viewport =
    {
        .x = 0.0f,
        .y = 0.0f,
        .width = (float)swapchain->swapchainExtent.width,
        .height = (float)swapchain->swapchainExtent.height,
        .minDepth = 0.0f,
        .maxDepth = 1.0f
    };

    VkRect2D scissor =
    {
        .offset = { 0, 0 },
        .extent = swapchain->swapchainExtent
    };

    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo;
    VkPipelineViewportStateCreateInfo viewportStateCreateInfo;
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo;
    VkPipelineColorBlendAttachmentState colourState;
    VkPipelineColorBlendStateCreateInfo colourBlendingCreateInfo;
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo;

    createPipelineLayout(viewport, scissor, rasterizationStateCreateInfo, viewportStateCreateInfo, multisampleStateCreateInfo, colourState, colourBlendingCreateInfo, pipelineLayoutCreateInfo);
    createPipeline(shaderStages, inputAssembly, vertexInputStateCreateInfo, viewportStateCreateInfo, rasterizationStateCreateInfo, multisampleStateCreateInfo, colourBlendingCreateInfo);
}

void UVK::VKGraphicsPipeline::createPipelineLayout(VkViewport& viewport, VkRect2D& scissor, VkPipelineRasterizationStateCreateInfo& rasterizationStateCreateInfo, VkPipelineViewportStateCreateInfo& viewportStateCreateInfo, VkPipelineMultisampleStateCreateInfo& multisampleStateCreateInfo, VkPipelineColorBlendAttachmentState& colourState, VkPipelineColorBlendStateCreateInfo& colourBlendingCreateInfo, VkPipelineLayoutCreateInfo& pipelineLayoutCreateInfo)
{
    viewportStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .pViewports = &viewport,
        .scissorCount = 1,
        .pScissors = &scissor
    };

    rasterizationStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_BACK_BIT,
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable = VK_FALSE,
        .lineWidth = 1.0f
    };

    // TODO: Implement multisampling
    multisampleStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
        .sampleShadingEnable = VK_FALSE
    };

    // TODO: Blending
    colourState =
    {
        .blendEnable = VK_TRUE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp = VK_BLEND_OP_ADD,
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
    };


    colourBlendingCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable = VK_FALSE,
        .attachmentCount = 1,
        .pAttachments = &colourState
    };

    pipelineLayoutCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 1,
        .pSetLayouts = descriptorSetLayout,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr,
    };

    if (vkCreatePipelineLayout(device->logicalDevice, &pipelineLayoutCreateInfo, nullptr, &layout) != VK_SUCCESS)
    {
        logger.consoleLog("Creation of Vulkan graphics pipeline failed", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    // TODO: Add depth stencil
}

void UVK::VKGraphicsPipeline::createRenderPass()
{
    const VkAttachmentDescription colourAttachment =
    {
        .format = swapchain->swapchainFormat,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
    };

    constexpr VkAttachmentReference colourAttachmentReference =
    {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    const VkSubpassDescription subpass =
    {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .colorAttachmentCount = 1,
        .pColorAttachments = &colourAttachmentReference
    };

    constexpr VkSubpassDependency subpassDependencies[2] =
    {
        {
            .srcSubpass = VK_SUBPASS_EXTERNAL,
            .dstSubpass = 1,
            .srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .srcAccessMask = VK_ACCESS_MEMORY_READ_BIT,
            .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            .dependencyFlags = 0
        },
        {
            .srcSubpass = 0,
            .dstSubpass = VK_SUBPASS_EXTERNAL,
            .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            .dstAccessMask = VK_ACCESS_MEMORY_READ_BIT,
            .dependencyFlags = 0
        }
    };

    const VkRenderPassCreateInfo renderPassCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = &colourAttachment,
        .subpassCount = 1,
        .pSubpasses = &subpass,
        .dependencyCount = 2,
        .pDependencies = subpassDependencies
    };

    auto result = vkCreateRenderPass(device->logicalDevice, &renderPassCreateInfo, nullptr, &renderPass);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan Render Pass!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}

void UVK::VKGraphicsPipeline::createPipeline(VkPipelineShaderStageCreateInfo* shaderStages, const VkPipelineInputAssemblyStateCreateInfo& inputAssembly, VkPipelineVertexInputStateCreateInfo& vertexInputStateCreateInfo, const VkPipelineViewportStateCreateInfo& viewportStateCreateInfo, const VkPipelineRasterizationStateCreateInfo& rasterizationStateCreateInfo, const VkPipelineMultisampleStateCreateInfo& multisampleStateCreateInfo, const VkPipelineColorBlendStateCreateInfo& colourBlendingCreateInfo)
{
    const VkGraphicsPipelineCreateInfo pipelineCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = 2,
        .pStages = shaderStages,
        .pVertexInputState = &vertexInputStateCreateInfo,
        .pInputAssemblyState = &inputAssembly,
        .pViewportState = &viewportStateCreateInfo,
        .pRasterizationState = &rasterizationStateCreateInfo,
        .pMultisampleState = &multisampleStateCreateInfo,
        .pDepthStencilState = nullptr,
        .pColorBlendState = &colourBlendingCreateInfo,
        .pDynamicState = nullptr,
        .layout = layout,
        .renderPass = renderPass,
        .subpass = 0,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1
    };

    auto result = vkCreateGraphicsPipelines(device->logicalDevice, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &graphicsPipeline);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan Graphics Pipeline!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}

VkPipelineLayout &UVK::VKGraphicsPipeline::pipelineLayout()
{
    return layout;
}
