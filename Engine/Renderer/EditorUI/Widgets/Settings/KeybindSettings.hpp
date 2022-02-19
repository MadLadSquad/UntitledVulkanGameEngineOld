// KeybindSettings.cpp
// Last update 18/2/2022 by Madman10K
#pragma once

namespace UVK::KeybindSettingsWidget
{
    void showKeySelect(const char* name, uint16_t& key);
    void displayKeybindsEditor(bool& bReturn, bool& bOpen);
    void displayKeybindsGame(bool& bReturn, bool& bOpen);
}