#include "Renderer.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include "OpenGL/GLRenderer.hpp"
#include "Vulkan/VulkanRenderer.hpp"
#include <yaml.h>

UVK::Renderer::Renderer(UVK::Level* lvl, bool bUsesEditor) noexcept
{
    startRenderer(lvl, bUsesEditor);
}

void UVK::Renderer::switchRenderer() noexcept
{
    if (global.bUsesVulkan) global.bUsesVulkan = false;
    else global.bUsesVulkan = true;

    global.rendererSettings.saveSettings();

    GameInstance::exit();
}

void UVK::RendererSettings::saveSettings() const noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "vulkan" << YAML::Value << global.bUsesVulkan;
    out << YAML::Key << "theme" << YAML::Value << themeLoc;
    out << YAML::Key << "v-sync" << YAML::Value << bVsync;
    out << YAML::Key << "v-sync-immediate" << YAML::Value << bVsyncImmediate;
    out << YAML::Key << "msaa-samples" << YAML::Value << samples;
    out << YAML::Key << "sample-rate-shading" << YAML::Value << sampleRateShading;
    out << YAML::Key << "sample-rate-shading-mult" << YAML::Value << sampleRateShadingMult;

    out << YAML::EndMap;

    std::ofstream fileout("../Config/Settings/Renderer.yaml");
    fileout << out.c_str();
}

void UVK::Renderer::startRenderer(UVK::Level* lvl, bool bUsesEditor) noexcept
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

void UVK::Renderer::loadSettings() noexcept
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
        if (a["msaa-samples"])
            rs->samples = a["msaa-samples"].as<uint32_t>();
        if (a["sample-rate-shading"])
            rs->sampleRateShading = a["sample-rate-shading"].as<bool>();
        if (a["sample-rate-shading-mult"])
            rs->sampleRateShadingMult = a["sample-rate-shading-mult"].as<float>();
    }
    else
    {
        global.bUsesVulkan = false;
    }
}

bool& UVK::Renderer::getVSync() noexcept
{
    return global.rendererSettings.bVsync;
}

void UVK::Renderer::saveSettings() noexcept
{
    global.rendererSettings.saveSettings();
}

bool& UVK::Renderer::getImmediateRender() noexcept
{
    return global.rendererSettings.bVsyncImmediate;
}

uint32_t& UVK::Renderer::msaaSampleCount() noexcept
{
    return global.rendererSettings.samples;
}

bool& UVK::Renderer::sampleRateShading() noexcept
{
    return global.rendererSettings.sampleRateShading;
}

float& UVK::Renderer::sampleRateShadingMult() noexcept
{
    return global.rendererSettings.sampleRateShadingMult;
}
