// Renderer.cpp
// Last update 18/2/2022 by Madman10K
#include "Renderer.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include "OpenGL/GLRenderer.hpp"
#include "Vulkan/VulkanRenderer.hpp"
#include <yaml.h>

UVK::Renderer::Renderer(UVK::Level* lvl, bool bUsesEditor)
{
    startRenderer(lvl, bUsesEditor);
}

void UVK::Renderer::switchRenderer()
{
    if (global.bUsesVulkan) global.bUsesVulkan = false;
    else global.bUsesVulkan = true;

    global.rendererSettings.saveSettings();

    GameInstance::exit();
}

void UVK::RendererSettings::saveSettings() const
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "vulkan" << YAML::Value << global.bUsesVulkan;
    out << YAML::Key << "theme" << YAML::Value << themeLoc;
    out << YAML::Key << "v-sync" << YAML::Value << bVsync;
    out << YAML::Key << "v-sync-immediate" << YAML::Value << bVsyncImmediate;
    //out << YAML::Key << "max-saved-transactions" << YAML::Value << maxSavedTransactions;
    //out << YAML::Key << "filesystem-file-padding" << YAML::Value << global.instance->editor->filesystemWidgetData.padding;
    //out << YAML::Key << "filesystem-file-thumbnail-size" << YAML::Value << global.instance->editor->filesystemWidgetData.imageSize;
    //out << YAML::Key << "filesystem-using-previews" << YAML::Value << global.instance->editor->filesystemWidgetData.bUsePreviews;
    //out << YAML::Key << "filesystem-max-preview-files" << YAML::Value << global.instance->editor->filesystemWidgetData.maxFileNum;

    out << YAML::EndMap;

    std::ofstream fileout("../Config/Settings/Renderer.yaml");
    fileout << out.c_str();
}

void UVK::Renderer::startRenderer(UVK::Level* lvl, bool bUsesEditor)
{
    loadSettings();

    if (global.bUsesVulkan)
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
            global.bUsesVulkan = a["vulkan"].as<bool>();

        if (a["theme"])
            rs->themeLoc = a["theme"].as<std::string>();

        if (a["v-sync"])
            rs->bVsync = a["v-sync"].as<bool>();

        if (a["v-sync-immediate"])
            rs->bVsyncImmediate = a["v-sync-immediate"].as<bool>();
    }
    else
    {
        global.bUsesVulkan = false;
    }
}

bool& UVK::Renderer::getVSync()
{
    return global.rendererSettings.bVsync;
}

void UVK::Renderer::saveSettings()
{
    global.rendererSettings.saveSettings();
}

bool& UVK::Renderer::getImmediateRender()
{
    return global.rendererSettings.bVsyncImmediate;
}