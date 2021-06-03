// Renderer.hpp
// Last update 6/5/2021 by Madman10K
#pragma once
#include "OpenGL/GLRenderer.hpp"
#include "Vulkan/VulkanRenderer.hpp"
#include <yaml.h>

namespace UVK
{
    /**
     * @brief Manages the currently used renderer and can switch renderers
     */
    class Renderer
    {
    public:
        Renderer() = delete;
        Renderer(UVK::Level* lvl, bool bUsesEditor);

        void switchRenderer();
        void saveSettings() const;
    private:
        void loadSettings();
        void startRenderer(UVK::Level* lvl, bool bUsesEditor);

        bool bIsVulkan = false;
        std::string theme;
    };
}