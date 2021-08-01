// VKPipeline.cpp
// Last update 1/8/2021 by Madman10K
#include "VKPipeline.hpp"

void UVK::VKPipeline::begin()
{
    instance.create();

    swapchain.set(&instance, &device);
    swapchain.createSurface();

    device.set(&instance.getData(), &swapchain);
    swapchain.createSwapchain();

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
