// Renderer.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include "OpenGL/GLRenderer.hpp"
#include "Vulkan/VulkanRenderer.hpp"
#include <yaml.h>

namespace UVK
{
    class Renderer
    {
    public:
        Renderer()
        {
            startRenderer();
        }

        void switchRenderer()
        {
            if (bIsVulkan)bIsVulkan = true;
            else bIsVulkan = false;
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
            YAML::Emitter out;
            out << YAML::BeginMap;

            out << YAML::Key << "vulkan" << YAML::Value << bIsVulkan;

            out << YAML::EndMap;

            std::ofstream fileout("Config/Settings/Renderer.yaml");
            fileout << out.c_str();
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

        bool bIsVulkan = false;

    };
}