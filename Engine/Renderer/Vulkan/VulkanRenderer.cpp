// VulkanRenderer.cpp
// Last update 27/5/2021 by Madman10K
#ifndef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include <Renderer/Window/Window.hpp>
#include "VulkanRenderer.hpp"
#include "Components/VKCamera.hpp"
#include "Components/VKFramebuffer.hpp"
#include "Components/VKMesh.hpp"
#include "Components/VKShader.hpp"

void UVK::VulkanRenderer::start()
{
    currentWindow.createWindow();

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

    GLfloat deltaTime;
    GLfloat lastTime = 0;

    while (!glfwWindowShouldClose(currentWindow.getWindow()))
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
