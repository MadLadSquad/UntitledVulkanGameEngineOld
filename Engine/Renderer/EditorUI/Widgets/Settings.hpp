// Settings.hpp
// Last update 2/9/2021 by Madman10K
#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include <iostream>

namespace Settings
{
    void showKeySelect(const char* name, uint16_t& key);

    bool displayWindow(bool& bOpen);
    bool displayRenderer(bool& bOpen);
    bool displayKeybindEditor(bool& bOpen);
    bool displayKeybindGame(bool& bOpen);
    bool displayThemeEditor(bool& bOpen);
    bool displayProjectSettings(std::string& name, std::string& ver, std::string& enginever, std::string& startupLevel, bool& bOpen);
}
#endif