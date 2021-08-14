// VKPipeline.cpp
// Last update 12/8/2021 by Madman10K
#include "VKPipeline.hpp"

void UVK::VKPipeline::begin()
{
    instance.create();

    swapchain.set(&instance, &device);
    swapchain.createSurface();

    device.set(&instance.getData(), &swapchain);
    swapchain.createSwapchain();

    graphicsPipeline = VKGraphicsPipeline(&device.device, &swapchain);
    graphicsPipeline.create();
}

void UVK::VKPipeline::tick()
{

}

void UVK::VKPipeline::end()
{
    graphicsPipeline.destroy();
    swapchain.destroySwapchain();
    swapchain.destroySurface();
    device.destroyLogicalDevice();
    instance.destroy();
}
