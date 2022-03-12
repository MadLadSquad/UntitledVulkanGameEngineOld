#include "GraphicsPipeline.hpp"
#include "Swapchain.hpp"

UVK::GraphicsPipeline::GraphicsPipeline(UVK::VKDevice& dev, Swapchain& swap)
{
    device = &dev;
    swapchain = &swap;
}

UVK::GraphicsPipeline::~GraphicsPipeline()
{
    destroyGraphicsPipeline();
}

void UVK::GraphicsPipeline::createGraphicsPipeline()
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
            throw std::runtime_error(" ");
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

    constexpr VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 0,
        .pVertexBindingDescriptions = nullptr,
        .vertexAttributeDescriptionCount = 0,
        .pVertexAttributeDescriptions = nullptr
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
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
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

    constexpr VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 0,
        .pSetLayouts = nullptr,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr,
    };

    auto result = vkCreatePipelineLayout(device->getDevice(), &pipelineLayoutCreateInfo, nullptr, &pipelineLayout);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a Vulkan graphics pipeline layout! Error code: ", UVK_LOG_TYPE_ERROR, result);
        throw std::runtime_error(" ");
    }

    // TODO: set up depth stencil testing


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
        .pDepthStencilState = nullptr,
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
        throw std::runtime_error(" ");
    }

    for (const auto& a : shaders)
        vkDestroyShaderModule(device->getDevice(), a.module, nullptr);
}

void UVK::GraphicsPipeline::destroyGraphicsPipeline()
{
    vkDestroyPipeline(device->getDevice(), graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device->getDevice(), pipelineLayout, nullptr);
    vkDestroyRenderPass(device->getDevice(), renderPass, nullptr);
}

void UVK::GraphicsPipeline::createRenderPass()
{
    const VkAttachmentDescription colourAttachment =
    {
        .format = swapchain->surfaceFormat.format,
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
        .pColorAttachments = &colourAttachmentReference,
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
        .attachmentCount = 1,
        .pAttachments = &colourAttachment,
        .subpassCount = 1,
        .pSubpasses = &subpass,
        .dependencyCount = 2,
        .pDependencies = subpassDependency
    };

    auto result = vkCreateRenderPass(device->getDevice(), &renderPassCreateInfo, nullptr, &renderPass);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan render pass! Error code: ", UVK_LOG_TYPE_ERROR, result);
        throw std::runtime_error(" ");
    }
}
