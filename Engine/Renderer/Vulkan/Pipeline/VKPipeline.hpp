// VKPipeline.hpp
// Last update 16/8/2021 by Madman10K
#pragma once
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif
#include "VKInstance.hpp"
#include "VKDevice.hpp"
#include "VKGraphicsPipeline.hpp"
#include "VKPushConstant.hpp"
#include "VKSwapchain.hpp"
#include "VKCommandBuffers.hpp"
#include "../Components/VKStructs.hpp"
#include "VKDraw.hpp"
#include "../Components/VKMesh.hpp"

namespace UVK
{
    /**
     * @brief Manages the whole renderer pipeline, not to be confused with VKGraphicsPipeline which is the actual
     * graphics pipeline, this is merely a manager
     */
    class VKPipeline
    {
    public:
        VKPipeline() = default;
    private:
        friend class VulkanRenderer;

        void begin();
        void tick();
        void end();
#ifndef __APPLE__
        VKInstance instance;
        Device device;
        VKGraphicsPipeline graphicsPipeline;

        VKPushConstant pushConstant;
        VKSwapchain swapchain;
        VKCommandBuffers commandBuffers;

        VKDraw draw;
        VKMesh mesh1;
#endif
    };
}
