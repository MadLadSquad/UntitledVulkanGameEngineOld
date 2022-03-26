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
        static bool displayProjectSettings(std::string& name, std::string& ver, std::string& enginever, std::string& startupLevel, bool& bOpen) noexcept;
    };
}
#endif