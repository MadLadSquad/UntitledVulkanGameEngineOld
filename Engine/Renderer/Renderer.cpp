// Renderer.cpp
// Last update 6/7/2021 by Madman10K
#include <GL/glew.h>
#include "Renderer.hpp"
#include <Engine/Core/Core/Global.hpp>

UVK::Renderer::Renderer(UVK::Level* lvl, bool bUsesEditor)
{
    startRenderer(lvl, bUsesEditor);
}

void UVK::Renderer::switchRenderer()
{
    if (rs->bVulkan) rs->bVulkan = false;
    else rs->bVulkan = true;
}

void UVK::RendererSettings::saveSettings() const
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "vulkan" << YAML::Value << bVulkan;
    out << YAML::Key << "theme" << YAML::Value << themeLoc;

    out << YAML::EndMap;

    std::ofstream fileout("../Config/Settings/Renderer.yaml");
    fileout << out.c_str();
}

void UVK::Renderer::startRenderer(UVK::Level* lvl, bool bUsesEditor)
{
    loadSettings();

    global.bUsesVulkan = rs->bVulkan;
    if (rs->bVulkan)
    {
        VulkanRenderer renderer{};
        renderer.run();
    }
    else
    {
        GLRenderer renderer(lvl, bUsesEditor, rs->themeLoc.c_str());
    }
}

void UVK::Renderer::loadSettings()
{
    YAML::Node a;
    bool bUsesConf = true;

    rs = &global.rendererSettings;

    try
    {
        a = YAML::LoadFile("../Config/Settings/Renderer.yaml");
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
            rs->bVulkan = a["vulkan"].as<bool>();
        }

        if (a["theme"])
        {
            rs->themeLoc = a["theme"].as<std::string>();
        }
    }
    else
    {
        rs->bVulkan = false;
    }
}