// VulkanRenderer.cpp
// Last update 18/2/2022 by Madman10K
#ifndef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include "VulkanRenderer.hpp"
#include "Renderer/EditorUI/Classes/EditorLevel.hpp"
#include "VKEntityManager.hpp"
#include "Components/Instance.hpp"
#include "Components/Device.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <glfw3.h>
#include <Core/Events/Events.hpp>

void UVK::VulkanRenderer::run()
{
    global.window.createWindow();
    VKInstance instance{};
    VKDevice device(instance);
    instance.create();
    device.createDevice();

    while (!glfwWindowShouldClose(global.window.getWindow()))
    {
        glfwPollEvents();
    }
    device.destroyDevice();
    instance.destroy();
}
#endif