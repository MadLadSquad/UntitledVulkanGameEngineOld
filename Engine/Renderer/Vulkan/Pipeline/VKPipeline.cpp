// VKPipeline.cpp
// Last update 16/8/2021 by Madman10K
#include "VKPipeline.hpp"
#include "../Components/VKMesh.hpp"

void UVK::VKPipeline::begin()
{
    instance.create();

    swapchain.set(&instance, &device);
    swapchain.createSurface();

    device.set(&instance.getData(), &swapchain);
    swapchain.createSwapchain();

    graphicsPipeline = VKGraphicsPipeline(&device.device, &swapchain);
    graphicsPipeline.create();

    swapchain.addRenderPassPointer(&graphicsPipeline.getRenderPass(), &graphicsPipeline.data());
    swapchain.createFramebuffers();

    std::vector<VKVertex> vertices;

    VKVertex b(FVector4(0.5f, -0.5f, 0.0f, 1.0f), FVector4(0.0f, 1.0f, 0.0f, 1.0f));
    VKVertex a(FVector4(0.5f, 0.5f, 0.0f, 1.0f), FVector4(1.0f, 0.0f, 0.0f, 1.0f));
    VKVertex c(FVector4(-0.5f, 0.5f, 0.0f, 1.0f), FVector4(0.0f, 0.0f, 1.0f, 1.0f));
    auto d = VKVertex(FVector4(-0.5f, -0.5f, 0.0f, 1.0f), FVector4(1.0f, 1.0f, 0.0f, 1.0f));

    vertices.push_back(b);
    vertices.push_back(a);
    vertices.push_back(c);
    vertices.push_back(d);

    std::vector<uint32_t> indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    mesh1 = VKMesh(&device.device, device.queue, commandBuffers.getCommandPool(),vertices, indices);

    commandBuffers = VKCommandBuffers(&device, swapchain.framebuffers, &graphicsPipeline.data(), &graphicsPipeline.getRenderPass());
    commandBuffers.createCommandPool();

    mesh1.create();

    commandBuffers.createCommandbuffers();
    commandBuffers.recordCommands(mesh1);

    draw = VKDraw(&device, &swapchain, &commandBuffers);
    draw.createSynchronisation();
}

void UVK::VKPipeline::tick()
{
    draw.getNextImage();
}

void UVK::VKPipeline::end()
{
    draw.destroySynchronisasion();
    commandBuffers.destroyCommandPool();
    mesh1.clear();
    swapchain.destroyFramebuffers();
    graphicsPipeline.destroy();
    swapchain.destroySwapchain();
    swapchain.destroySurface();
    device.destroyLogicalDevice();
    instance.destroy();
}
