// VKPipeline.hpp
// Last update 28/5/2021 by Madman10K
#pragma once
#include <vulkan/vulkan.h>
#include "VKInstance.hpp"
#include "VKDevice.hpp"
#include "VKGraphicsPipeline.hpp"
#include "VKPushConstant.hpp"
#include "VKSwapchain.hpp"

namespace UVK
{
    class VKPipeline
    {
    public:
        VKPipeline() = default;

        void begin();
        void tick();
        void end();
    private:
        VKInstance instance;
        Device device;
        VKGraphicsPipeline graphicsPipeline;

        VKPushConstant pushConstant;
        VKSwapchain swapchain;
    };
}