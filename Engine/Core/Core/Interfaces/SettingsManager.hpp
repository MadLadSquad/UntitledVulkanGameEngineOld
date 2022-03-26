#pragma once

namespace UVK
{
    struct RendererSettings;

    class UVK_PUBLIC_API SettingsManager
    {
    public:
        SettingsManager() = delete;
        SettingsManager(const SettingsManager&) = delete;
        void operator=(SettingsManager const&) = delete;

        // Saves all settings
        static void saveSettings() noexcept;
        static void saveRendererSettings() noexcept;
        static void saveEditorKeybindSettings() noexcept;
        static void saveKeybindSettings() noexcept;
        static void saveWindowSettings() noexcept;
        [[maybe_unused]] static void saveWindowAndKeybindSettings() noexcept;

        static RendererSettings& getRendererSettings() noexcept;
    };
}