// VKPipeline.cpp
// Last update 2/7/2021 by Madman10K
#include "VKPipeline.hpp"

void UVK::VKPipeline::begin()
{
    instance.create();

    swapchain.set(&instance, &device);
    swapchain.createSurface();

    device.set(&instance.getData(), &swapchain);
    swapchain.createSwapchain();
}

void UVK::VKPipeline::tick()
{

}

void UVK::VKPipeline::end()
{
    swapchain.destroySwapchain();
    swapchain.destroySurface();
    device.destroyLogicalDevice();
    instance.destroy();
}
