#pragma once

namespace UVK::KeybindSettingsWidget
{
    void showKeySelect(const char* name, uint16_t& key) noexcept;
    void displayKeybindsEditor(bool& bReturn, bool& bOpen) noexcept;
    void displayKeybindsGame(bool& bReturn, bool& bOpen) noexcept;
}