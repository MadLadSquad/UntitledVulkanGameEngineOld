// VKPipeline.hpp
// Last update 28/5/2021 by Madman10K
#pragma once
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif
#include "VKInstance.hpp"
#include "VKDevice.hpp"
#include "VKGraphicsPipeline.hpp"
#include "VKPushConstant.hpp"
#include "VKSwapchain.hpp"
#include "../Components/VKStructs.hpp"

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
#ifndef __APPLE__
        VKInstance instance;
        Device device;
        VKGraphicsPipeline graphicsPipeline;

        VKPushConstant pushConstant;
        VKSwapchain swapchain;
#endif
    };
}
