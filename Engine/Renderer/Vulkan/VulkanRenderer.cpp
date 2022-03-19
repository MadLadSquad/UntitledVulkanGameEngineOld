// VulkanRenderer.cpp
// Last update 26/02/2022 by Madman10K
#ifndef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include "VulkanRenderer.hpp"
#include "Renderer/EditorUI/Classes/EditorLevel.hpp"
#include "VKEntityManager.hpp"
#include "Components/Instance.hpp"
#include "Components/Device.hpp"
#include "Components/Swapchain.hpp"
#include "Components/GraphicsPipeline.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <glfw3.h>
#include <Core/Events/Events.hpp>
#include <UVKShaderCompiler/Src/Functions.hpp>

void UVK::VulkanRenderer::run()
{
    // Set the UVKShaderCompiler path and check for recompilation
    USC::setPrefixDir("../");
    USC::checkForCompile();

    global.window.createWindow();

    VKInstance instance{};
    Swapchain swapchain{};
    VKDevice device(instance);
    swapchain = Swapchain(instance, device);
    GraphicsPipeline pipeline(device, swapchain);

    instance.create();
    swapchain.createSurface();
    device.createDevice(swapchain);
    swapchain.createSwapchain();
    pipeline.createRenderPass();
    pipeline.createGraphicsPipeline();
    swapchain.createFramebuffers(pipeline);
    swapchain.createCommandPool();
    swapchain.createCommandBuffers();

    swapchain.recordCommands();

    while (!glfwWindowShouldClose(global.window.getWindow()))
    {
        glfwPollEvents();
    }
    swapchain.destroyCommandBuffers();
    swapchain.destroyCommandPool();
    swapchain.destroyFramebuffers();
    swapchain.destroySwapchain();
}
#endif