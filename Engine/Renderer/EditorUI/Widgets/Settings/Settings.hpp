#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include <iostream>

namespace UVK
{
    class Editor;
    class SettingsWidgets
    {
    private:
        friend class Editor;

        static bool displayEditorSettings(bool& bOpen, Editor& editor) noexcept;
        static bool displayWindow(bool& bOpen) noexcept;
        static bool displayRenderer(bool& bOpen, Editor& editor) noexcept;
        static bool displayKeybindEditor(bool& bOpen) noexcept;
        static bool displayKeybindGame(bool& bOpen) noexcept;
        static bool displayThemeEditor(bool& bOpen) noexcept;
        static bool displayProjectSettings(UVK::FString& name, UVK::FString& ver, UVK::FString& enginever, UVK::FString& startupLevel, bool& bOpen) noexcept;
    };
}
#endif