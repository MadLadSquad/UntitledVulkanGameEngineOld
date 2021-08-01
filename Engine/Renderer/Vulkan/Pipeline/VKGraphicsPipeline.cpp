// VKGraphicsPipeline.cpp
// Last update 1/8/2021 by Madman10K
#include "VKGraphicsPipeline.hpp"
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

void UVK::VKGraphicsPipeline::create()
{

}

void UVK::VKGraphicsPipeline::destroy()
{

}

void UVK::VKGraphicsPipeline::createVertextShaderStage()
{
    VkPipelineShaderStageCreateInfo shaderStageCreateInfo = {};
    shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    //shaderStageCreateInfo.module =
}
