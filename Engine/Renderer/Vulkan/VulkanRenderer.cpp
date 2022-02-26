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
#include <Engine/Core/Core/Global.hpp>
#include <glfw3.h>
#include <Core/Events/Events.hpp>

void UVK::VulkanRenderer::run()
{
    global.window.createWindow();
    VKInstance instance{};
    Swapchain swapchain{};
    VKDevice device(instance);
    swapchain = Swapchain(instance, device);
    instance.create();
    swapchain.createSurface();
    device.createDevice(swapchain);

    while (!glfwWindowShouldClose(global.window.getWindow()))
    {
        glfwPollEvents();
    }
}
#endif