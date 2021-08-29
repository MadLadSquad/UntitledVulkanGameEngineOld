// Settings.hpp
// Last update 18/7/2021 by Madman10K
#pragma once
#include <iostream>

namespace Settings
{
    void showKeySelect(const char* name, uint16_t& key);

    void displayWindow(bool& bOpen);
    void displayRenderer(bool& bOpen);
    void displayKeybindEditor(bool& bOpen);
    void displayKeybindGame(bool& bOpen);
    void displayThemeEditor(bool& bOpen);
    void displayProjectSettings(std::string& name, std::string& ver, std::string& enginever, std::string& startupLevel, bool& bOpen);
}