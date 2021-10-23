// Renderer.hpp
// Last update 6/7/2021 by Madman10K
#pragma once
#include "OpenGL/GLRenderer.hpp"
#include "Vulkan/VulkanRenderer.hpp"
#include <yaml.h>

namespace UVK
{
    //struct RendererSettings;
    /**
     * @brief Manages the currently used renderer and can switch renderers
     */
    class Renderer
    {
    public:
        Renderer() = delete;
        Renderer(UVK::Level* lvl, bool bUsesEditor);
        Renderer(const Renderer&) = delete;
        void operator=(Renderer const&) = delete;

        // Will switch your renderer API, save the rendering settings and shut down the application
        static void switchRenderer();

        // When V-Sync is off, in Vulkan we have 2 presentation modes that are going to be toggled by this boolean.
        // If the boolean is true we will render in 'VK_PRESENT_MODE_IMMEDIATE_KHR', but if it is false we will present
        // in 'VK_PRESENT_MODE_FIFO_RELAXED_KHR', this however depends on if the graphics card supports all 2 modes so
        // setting this boolean to true will not always result in the desired effect. You can read about what the
        // presentation modes do here:
        // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkPresentModeKHR.html#_description
        static bool& getImmediateRender();
        static bool& getVSync();
        static void saveSettings();
    private:
        friend class Editor;

        void loadSettings();
        static void loadFilesystemSettings();
        void startRenderer(UVK::Level* lvl, bool bUsesEditor);

        RendererSettings* rs{};
    };
}