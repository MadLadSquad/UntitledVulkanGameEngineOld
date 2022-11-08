#include "RendererInterface.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <yaml.h>
#include <Engine/GameFramework/GameplayClasses/GameInstance.hpp>

void UVK::Renderer::switchRenderer() noexcept
{
    if (global.bUsesVulkan) global.bUsesVulkan = false;
    else global.bUsesVulkan = true;

    global.rendererSettings.saveSettings();

    GameInstance::exit();
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