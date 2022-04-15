#include "GraphicsPipeline.hpp"
#include "Swapchain.hpp"
#include "Depth.hpp"

UVK::GraphicsPipeline::GraphicsPipeline(UVK::VKDevice& dev, Swapchain& swap, const VKDescriptors& desc, VKDepthBuffer& depth) noexcept
{
    device = &dev;
    swapchain = &swap;
    descriptors = &desc;
    depthBuffer = &depth;
}

void UVK::GraphicsPipeline::createGraphicsPipeline() noexcept
{
    std::vector<VKShader> shaders;
    std::vector<VkPipelineShaderStageCreateInfo> stages;

    VKShader::each([&](VKShader& shader){
        // TODO: Remove this
        if (shader.name.starts_with("../Content/Engine/vkshader."))
            shaders.push_back(shader);
    });

    for (auto& a : shaders)
    {
        auto code = a.getShaderBytecode();

        const VkShaderModuleCreateInfo shaderModuleCreateInfo =
        {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .codeSize = code.size(),
            .pCode = reinterpret_cast<uint32_t*>(code.data()),
        };
        VkShaderModule module;
        VkResult result = vkCreateShaderModule(device->getDevice(), &shaderModuleCreateInfo, nullptr, &module);
        if (result != VK_SUCCESS)
        {
            logger.consoleLog("Failed to create a Vulkan shader module! Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }

        a.info = VkPipelineShaderStageCreateInfo
        {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = static_cast<VkShaderStageFlagBits>(a.type),
            .module = module,
            .pName = "main"
        };
        a.module = module;
        stages.push_back(a.info);
    }

    constexpr VkVertexInputBindingDescription bindingDescription =
    {
        .binding = 0,
        .stride = sizeof(VKVertex),
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
    };

    constexpr VkVertexInputAttributeDescription attributeDescriptions[3] =
    {
        {
            .location = 0,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32A32_SFLOAT,
            .offset = offsetof(VKVertex, pos)
        },
        {
            .location = 1,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32A32_SFLOAT,
            .offset = offsetof(VKVertex, colour)
        },
        {
            .location = 2,
            .binding = 0,
            .format = VK_FORMAT_R32G32_SFLOAT,
            .offset = offsetof(VKVertex, uv)
        }
    };

    const VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &bindingDescription,
        .vertexAttributeDescriptionCount = 3,
        .pVertexAttributeDescriptions = attributeDescriptions
    };

    constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE,
    };

    const VkViewport viewport =
    {
        .x = 0.0f,
        .y = 0.0f,
        .width = static_cast<float>(swapchain->extent.width),
        .height = static_cast<float>(swapchain->extent.height),
        .minDepth = 0.0f,
        .maxDepth = 1.0f
    };

    const VkRect2D scissor =
    {
        .offset =
        {
            0,
            0
        },
        .extent = swapchain->extent
    };

    const VkPipelineViewportStateCreateInfo viewportStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .pViewports = &viewport,
        .scissorCount = 1,
        .pScissors = &scissor
    };

    // TODO: Add dynamic state here
    // Starting rasterizer here
    constexpr VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,    // TODO: Check this out for wireframe
        .cullMode = VK_CULL_MODE_BACK_BIT,
        .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        .depthBiasEnable = VK_FALSE,                         // TODO: Might be interesting later
        .lineWidth = 1.0f,
    };

    // TODO: Visit this later for multisampling
    constexpr VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
        .sampleShadingEnable = VK_FALSE,
    };

    constexpr VkPipelineColorBlendAttachmentState colourState =
    {
        .blendEnable = VK_TRUE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp = VK_BLEND_OP_ADD,
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    };

    const VkPipelineColorBlendStateCreateInfo colourBlendingCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable = VK_FALSE,
        .attachmentCount = 1,
        .pAttachments = &colourState,
    };

    const VkDescriptorSetLayout descriptorSetLayouts[] =
    {
        descriptors->layout(),
        descriptors->samplerLayout()
    };

    const VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 2,
        .pSetLayouts = descriptorSetLayouts,
        .pushConstantRangeCount = 1,
        .pPushConstantRanges = &descriptors->getPushConstantRange(),
    };

    auto result = vkCreatePipelineLayout(device->getDevice(), &pipelineLayoutCreateInfo, nullptr, &pipelineLayout);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a Vulkan graphics pipeline layout! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    const VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable = VK_TRUE,
        .depthWriteEnable = VK_TRUE,
        .depthCompareOp = VK_COMPARE_OP_LESS,
        .depthBoundsTestEnable = VK_FALSE,
        .stencilTestEnable = VK_FALSE,
    };

    const VkGraphicsPipelineCreateInfo pipelineCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = static_cast<uint32_t>(stages.size()),
        .pStages = stages.data(),
        .pVertexInputState = &vertexInputStateCreateInfo,
        .pInputAssemblyState = &inputAssembly,
        .pTessellationState = nullptr,
        .pViewportState = &viewportStateCreateInfo,
        .pRasterizationState = &rasterizationStateCreateInfo,
        .pMultisampleState = &multisampleStateCreateInfo,
        .pDepthStencilState = &depthStencilStateCreateInfo,
        .pColorBlendState = &colourBlendingCreateInfo,
        .pDynamicState = nullptr,
        .layout = pipelineLayout,
        .renderPass = renderPass,
        .subpass = 0,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1
    };

    result = vkCreateGraphicsPipelines(device->getDevice(), VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &graphicsPipeline);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan graphics pipeline! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    for (const auto& a : shaders)
        vkDestroyShaderModule(device->getDevice(), a.module, nullptr);
}

void UVK::GraphicsPipeline::destroyGraphicsPipeline() noexcept
{
    vkDestroyPipeline(device->getDevice(), graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device->getDevice(), pipelineLayout, nullptr);
    vkDestroyRenderPass(device->getDevice(), renderPass, nullptr);
}

void UVK::GraphicsPipeline::createRenderPass() noexcept
{
    const VkAttachmentDescription descriptions[] =
    {
        {
            .format = swapchain->surfaceFormat.format,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
        },
        {
            .format = depthBuffer->getFormat(),
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
            .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
        }
    };

    constexpr VkAttachmentReference attachmentReferences[] =
    {
        {
            .attachment = 0,
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        },
        {
            .attachment = 1,
            .layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        }
    };

    const VkSubpassDescription subpass =
    {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .colorAttachmentCount = 1,
        .pColorAttachments = &attachmentReferences[0],
        .pDepthStencilAttachment = &attachmentReferences[1]
    };

    constexpr VkSubpassDependency subpassDependency[2] =
    {
        {
            .srcSubpass = VK_SUBPASS_EXTERNAL,
            .dstSubpass = 0,
            .srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .srcAccessMask = VK_ACCESS_MEMORY_READ_BIT,
            .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            .dependencyFlags = 0,
        },
        {
            .srcSubpass = 0,
            .dstSubpass = VK_SUBPASS_EXTERNAL,
            .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            .dstAccessMask = VK_ACCESS_MEMORY_READ_BIT,
            .dependencyFlags = 0,
        }
    };

    const VkRenderPassCreateInfo renderPassCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = 2,
        .pAttachments = descriptions,
        .subpassCount = 1,
        .pSubpasses = &subpass,
        .dependencyCount = 2,
        .pDependencies = subpassDependency
    };

    auto result = vkCreateRenderPass(device->getDevice(), &renderPassCreateInfo, nullptr, &renderPass);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan render pass! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

VkPipelineLayout& UVK::GraphicsPipeline::getPipelineLayout() noexcept
{
    return pipelineLayout;
}

VkRenderPass& UVK::GraphicsPipeline::getRenderPass() noexcept
{
    return renderPass;
}

VkPipeline& UVK::GraphicsPipeline::getPipeline() noexcept
{
    return graphicsPipeline;
}
