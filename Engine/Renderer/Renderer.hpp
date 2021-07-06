// Renderer.hpp
// Last update 2/7/2021 by Madman10K
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

        void switchRenderer();

    private:
        void loadSettings();
        void startRenderer(UVK::Level* lvl, bool bUsesEditor);

        RendererSettings* rs{};
    };
}