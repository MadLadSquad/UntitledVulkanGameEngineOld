// SettingsManager.hpp
// Last update 18/7/2021 by Madman10K
#pragma once

namespace UVK
{
    struct RendererSettings;

    class SettingsManager
    {
    public:
        // Saves all settings
        static void saveSettings();
        static void saveRendererSettings();
        static void saveEditorKeybindSettings();
        static void saveKeybindSettings();
        static void saveWindowSettings();
        static void saveWindowAndKeybindSettings();

        static RendererSettings& getRendererSettings();
    };
}