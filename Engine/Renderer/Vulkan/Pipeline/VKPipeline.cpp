// VKPipeline.cpp
// Last update 16/8/2021 by Madman10K
#include "VKPipeline.hpp"
#include <Core/Interfaces/WindowInterface.hpp>

void UVK::VKPipeline::begin()
{
    proj = Projection(45.0f, (float)(Window::windowSize().x / Window::windowSize().y), { 0.1f, 100.0f });
    proj.recalculateLH();

    instance.create(); // ~27ms

    swapchain.set(&instance, &device);
    swapchain.createSurface(); // 0.004ms

    device.set(&instance.getData(), &swapchain);
    swapchain.createSwapchain(VK_NULL_HANDLE); // between ~20ms and ~45ms

    descriptorSets = VKDescriptorSets(device.device, swapchain);
    descriptorSets.createDescriptorSetLayout();

    graphicsPipeline = VKGraphicsPipeline(&device.device, &swapchain, &descriptorSets.layout());
    graphicsPipeline.create(); // ~3ms

    swapchain.addRenderPassPointer(&graphicsPipeline.getRenderPass(), &graphicsPipeline.data());
    swapchain.createFramebuffers(); // 0.003ms

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

    mesh1 = VKMesh(&device.device, device.queue, commandBuffers.getCommandPool(),vertices, indices, graphicsPipeline.pipelineLayout());

    commandBuffers = VKCommandBuffers(&device, swapchain.framebuffers, &graphicsPipeline.data(), &graphicsPipeline.getRenderPass());
    commandBuffers.createCommandPool(); // ~0.03ms

    mesh1.create(); // ~3ms

    commandBuffers.createCommandbuffers(); // ~0.001ms

    descriptorSets.createUniformBuffers();
    descriptorSets.createDescriptorPool();
    descriptorSets.createDescriptorSets();

    commandBuffers.recordCommands(mesh1, descriptorSets.getDescriptorSets()); // ~0.02ms

    draw = VKDraw(&device, &swapchain, &commandBuffers);
    draw.createSynchronisation(); // ~0.05ms
}

void UVK::VKPipeline::tick()
{
    //commandBuffers.recordCommands(mesh1);
    draw.getNextImage(mesh1);
    /*if (!a)
    {
        //vkDeviceWaitIdle(device.device.logicalDevice);
        std::cout << "Stopped waiting" << std::endl;
        cleanupSwapchainAndSwapchainDependencies(true);

        swapchain.createSwapchain(swapchain.swapchain);

        graphicsPipeline = VKGraphicsPipeline(&device.device, &swapchain);
        graphicsPipeline.create();

        swapchain.addRenderPassPointer(&graphicsPipeline.getRenderPass(), &graphicsPipeline.data());
        swapchain.createFramebuffers();


        commandBuffers.createCommandbuffers();
        //commandBuffers.recordCommands(mesh1);
    }*/
}

void UVK::VKPipeline::end()
{
    vkDeviceWaitIdle(device.device.logicalDevice);
    descriptorSets.destroyDescriptorSetLayout();

    // Times recorded here combined contribute to ~40ms
    draw.destroySynchronisasion(); // ~0.3ms
    commandBuffers.destroyCommandPool(); // 0.009ms
    mesh1.clear(); // 0.33ms
    cleanupSwapchainAndSwapchainDependencies(false); // 21.017ms
    swapchain.destroySurface(); // 0.01ms
    device.destroyLogicalDevice(); // ~11.4ms
    instance.destroy(); // ~8ms
}

void UVK::VKPipeline::cleanupSwapchainAndSwapchainDependencies(bool rebuild)
{
    swapchain.destroyFramebuffers(); // 0.002ms

    if (rebuild)
    {
        vkFreeCommandBuffers(device.device.logicalDevice, commandBuffers.getCommandPool(), static_cast<uint32_t>(commandBuffers.getCommandBuffers().size()), commandBuffers.getCommandBuffers().data());
    }

    graphicsPipeline.destroy(); // 0.015ms
    swapchain.destroySwapchain(); // 21ms
}
