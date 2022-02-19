// Settings.hpp
// Last update 18/2/2022 by Madman10K
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

        static bool displayEditorSettings(bool& bOpen, Editor& editor);
        static bool displayWindow(bool& bOpen);
        static bool displayRenderer(bool& bOpen, Editor& editor);
        static bool displayKeybindEditor(bool& bOpen);
        static bool displayKeybindGame(bool& bOpen);
        static bool displayThemeEditor(bool& bOpen);
        static bool displayProjectSettings(std::string& name, std::string& ver, std::string& enginever, std::string& startupLevel, bool& bOpen);
    };
}
#endif