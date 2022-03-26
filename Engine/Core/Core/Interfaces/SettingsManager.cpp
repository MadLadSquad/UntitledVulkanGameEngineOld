#include "SettingsManager.hpp"
#include <Core/Global.hpp>

void UVK::SettingsManager::saveSettings() noexcept
{
    saveWindowSettings();
    saveRendererSettings();
    saveEditorKeybindSettings();
    saveKeybindSettings();
}

void UVK::SettingsManager::saveRendererSettings() noexcept
{
    global.rendererSettings.saveSettings();
}

void UVK::SettingsManager::saveEditorKeybindSettings() noexcept
{
    UVK::WindowInternal::saveEditorKeybinds();
}

void UVK::SettingsManager::saveKeybindSettings() noexcept
{
    UVK::WindowInternal::saveGameKeybinds();
}

UVK::RendererSettings& UVK::SettingsManager::getRendererSettings() noexcept
{
    return global.rendererSettings;
}

void UVK::SettingsManager::saveWindowSettings() noexcept
{
    global.window.saveWindowSettings();
}

void UVK::SettingsManager::saveWindowAndKeybindSettings() noexcept
{
    global.window.dumpConfig();
}
