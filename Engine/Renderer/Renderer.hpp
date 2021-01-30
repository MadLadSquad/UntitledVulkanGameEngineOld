// Renderer.hpp
// Last update 1/10/2021 by Madman10K
#pragma once
#include "OpenGL/GLRenderer.hpp"
#include "Vulkan/VulkanRenderer.hpp"
#include <yaml.h>

namespace UVK
{
    class Renderer
    {
    public:
        void switchRenderer()
        {
            if (bIsVulkan)
            {

            }
        }

        void startRenderer()
        {
            loadSettings();

            if (bIsVulkan)
            {
                VulkanRenderer renderer;

                renderer.start();
            }
            else
            {
                GLRenderer renderer;

                renderer.createWindow();
            }
        }


        void saveSettings()
        {

        }

    private:

        void loadSettings()
        {
            auto a = YAML::LoadFile("Config/Settings/Renderer.yaml");

            if (a["vulkan"])
            {
                bIsVulkan = a["vulkan"].as<bool>();
            }
        }

        bool bIsVulkan;

    };
}