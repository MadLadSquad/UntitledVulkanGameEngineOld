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
#include "Components/VKMesh.hpp"

void UVK::VulkanRenderer::run() noexcept
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

    std::vector<VKVertex> vertices =
    {
        {{-0.5f, -0.5f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}},
        {{0.5f, 0.5f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f}},

        {{-0.5f, -0.5f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}}
    };
    VKMesh mesh(device, vertices);
    std::vector<VKMesh> meshes = { mesh };
    swapchain.recordCommands(meshes);
    swapchain.createSynchronisation();

    while (!glfwWindowShouldClose(global.window.getWindow()))
    {
        glfwPollEvents();
        swapchain.draw();
    }
    vkDeviceWaitIdle(device.getDevice());
    mesh.destroyVertexBuffer();


    swapchain.destroySynchronisation();
    swapchain.destroyCommandBuffers();
    swapchain.destroyCommandPool();
    swapchain.destroyFramebuffers();
    swapchain.destroySwapchain();
}
#endif