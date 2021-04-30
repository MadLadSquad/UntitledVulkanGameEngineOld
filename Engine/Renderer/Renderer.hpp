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
        Renderer() = delete;
        Renderer(UVK::Level* lvl, bool bUsesEditor)
        {
            startRenderer(lvl, bUsesEditor);
        }

        void switchRenderer()
        {
            if (bIsVulkan)bIsVulkan = false;
            else bIsVulkan = true;
        }

        void saveSettings() const
        {
            YAML::Emitter out;
            out << YAML::BeginMap;

            out << YAML::Key << "vulkan" << YAML::Value << bIsVulkan;
            out << YAML::Key << "theme" << YAML::Value << theme;

            out << YAML::EndMap;

            std::ofstream fileout("Config/Settings/Renderer.yaml");
            fileout << out.c_str();
        }

    private:

        void loadSettings()
        {
            YAML::Node a;
            bool bUsesConf = true;

            try
            {
                a = YAML::LoadFile("Config/Settings/Renderer.yaml");
            }
            catch (YAML::BadFile&)
            {
                bUsesConf = false;

                logger.consoleLog("Invalid renderer file defaulting to OpenGL with default theme if the editor is in use!", UVK_LOG_TYPE_ERROR);
            }

            if (bUsesConf)
            {
                if (a["vulkan"])
                {
                    bIsVulkan = a["vulkan"].as<bool>();
                }

                if (a["theme"])
                {
                    theme = a["theme"].as<std::string>();
                }
            }
            else
            {
                bIsVulkan = false;
            }
        }

        void startRenderer(UVK::Level* lvl, bool bUsesEditor)
        {
            loadSettings();

            if (bIsVulkan)
            {
                VulkanRenderer renderer{};

                renderer.start();
            }
            else
            {
                GLRenderer renderer(lvl, bUsesEditor, theme);
            }
        }

        bool bIsVulkan = false;
        std::string theme;
    };
}