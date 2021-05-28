// VKPipeline.cpp
// Last update 28/5/2021 by Madman10K
#include "VKPipeline.hpp"

void UVK::VKPipeline::begin()
{
    instance.create();

    swapchain.set(&instance, &device);
    swapchain.createSurface();

    device.set(&instance.getData(), &swapchain);
}

void UVK::VKPipeline::tick()
{

}

void UVK::VKPipeline::end()
{
    device.destroyLogicalDevice();
    swapchain.destroySurface();
    instance.destroy();
}
