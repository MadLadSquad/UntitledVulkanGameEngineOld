// VKGraphicsPipeline.hpp
// Last update 12/8/2021 by Madman10K
#pragma once
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

namespace UVK
{
    class VKDevice;
    /**
     * @brief A Vulkan graphics pipeline manager
     */
    class VKGraphicsPipeline
    {
    public:
        VKGraphicsPipeline() = default;
        explicit VKGraphicsPipeline(VKDevice* dev);

        void create();
        void destroy();
    private:
        VKDevice* device;
        VkPipelineLayout layout;
        void createShaderStage(VkShaderModule& vertexModule, VkShaderModule& fragmentModule);
        void createViewport();
    };
}