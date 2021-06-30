// VulkanRenderer.cpp
// Last update 30/6/2021 by Madman10K
#ifndef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include <GL/glew.h>
#include <Engine/Core/Core/Global.hpp>
#include "VulkanRenderer.hpp"
#include "Components/VKFramebuffer.hpp"
#include "Components/VKMesh.hpp"
#include "Components/VKShader.hpp"

void UVK::VulkanRenderer::start()
{
    global.window.createWindow();

    pipeline.begin();
}

void UVK::VulkanRenderer::render()
{
    pipeline.tick();
}

void UVK::VulkanRenderer::cleanup()
{
    pipeline.end();
}

void UVK::VulkanRenderer::run()
{
    start();

    float deltaTime;
    float lastTime = 0;

    while (!glfwWindowShouldClose(global.window.getWindow()))
    {
        glfwPollEvents();

        auto now = (float)glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        render();
    }

    cleanup();
}


VkSurfaceFormatKHR UVK::VulkanRenderer::findSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &formats) {
    return VkSurfaceFormatKHR();
}
#endif
