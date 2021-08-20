// VulkanRenderer.cpp
// Last update 16/8/2021 by Madman10K
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
    Timer setup;
    setup.startRecording();
    start();

    float deltaTime;
    float lastTime = 0;
    setup.stopRecording();
    logger.consoleLog("Starting the Vulkan renderer took ", UVK_LOG_TYPE_NOTE, setup.getDuration(), "ms");

    while (!glfwWindowShouldClose(global.window.getWindow()))
    {
        glfwPollEvents();

        auto now = (float)glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        if (UVK::Input::getKey(Keys::W) == Keys::KeyPressed)
        {
            std::cout << deltaTime << std::endl;
        }
        render();
    }
    Timer clean;
    clean.startRecording();
    cleanup();
    clean.stopRecording();
    logger.consoleLog("Closing the Vulkan renderer took ", UVK_LOG_TYPE_NOTE, clean.getDuration(), "ms");
}
#endif