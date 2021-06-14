// Renderer.cpp
// Last update 27/5/2021 by Madman10K
#include <GL/glew.h>
#include "Renderer.hpp"
#include <Renderer/RendererResources.hpp>

UVK::Renderer::Renderer(UVK::Level* lvl, bool bUsesEditor)
{
    startRenderer(lvl, bUsesEditor);
}

void UVK::Renderer::switchRenderer()
{
    if (bIsVulkan)bIsVulkan = false;
    else bIsVulkan = true;
}

void UVK::Renderer::saveSettings() const
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "vulkan" << YAML::Value << bIsVulkan;
    out << YAML::Key << "theme" << YAML::Value << theme;

    out << YAML::EndMap;

    std::ofstream fileout("Config/Settings/Renderer.yaml");
    fileout << out.c_str();
}

void UVK::Renderer::startRenderer(UVK::Level *lvl, bool bUsesEditor)
{
    loadSettings();

    if (bIsVulkan)
    {
        currentWindow.getVulkan() = true;
        VulkanRenderer renderer{};
        renderer.run();
    }
    else
    {
        currentWindow.getVulkan() = false;
        GLRenderer renderer(lvl, bUsesEditor, theme);
    }
}

void UVK::Renderer::loadSettings()
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