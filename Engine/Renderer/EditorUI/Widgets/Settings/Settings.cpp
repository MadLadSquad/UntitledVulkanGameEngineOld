// Settings.cpp
// Last update 18/2/2022 by Madman10K
#include "Settings.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include "WindowSettings.hpp"
#include "RendererSettings.hpp"
#include "KeybindSettings.hpp"
#include "ProjectSettings.hpp"
#include "ThemeSettings.hpp"
#include "EditorSettings.hpp"

#define UVK_SETTINGS_WIDGET_BEGIN(x, y) bool bReturn = false; \
    if (!ImGui::IsPopupOpen(x)) \
        ImGui::OpenPopup(x); \
    if (ImGui::BeginPopupModal(x, &bOpen, y))

bool UVK::SettingsWidgets::displayWindow(bool& bOpen)
{
    UVK_SETTINGS_WIDGET_BEGIN("Window Settings", ImGuiWindowFlags_None)
        UVK::WindowSettingsWidget::display(bReturn, bOpen);
    return bReturn;
}

bool UVK::SettingsWidgets::displayRenderer(bool& bOpen, Editor& editor)
{
    UVK_SETTINGS_WIDGET_BEGIN("Renderer Settings", ImGuiWindowFlags_None)
        UVK::RendererSettingsWidget::display(bReturn, bOpen, editor);
    return bReturn;
}

bool UVK::SettingsWidgets::displayKeybindEditor(bool& bOpen)
{
    UVK_SETTINGS_WIDGET_BEGIN("Editor Keybinds", ImGuiWindowFlags_None)
        UVK::KeybindSettingsWidget::displayKeybindsEditor(bReturn, bOpen);
    return bReturn;
}

bool UVK::SettingsWidgets::displayKeybindGame(bool& bOpen)
{
    UVK_SETTINGS_WIDGET_BEGIN("Game Keybinds", ImGuiWindowFlags_MenuBar)
        UVK::KeybindSettingsWidget::displayKeybindsGame(bReturn, bOpen);
    return bReturn;
}

bool UVK::SettingsWidgets::displayThemeEditor(bool& bOpen)
{
    UVK_SETTINGS_WIDGET_BEGIN("Theme Editor", ImGuiWindowFlags_None)
        UVK::ThemeSettingsWidget::displayThemeSettings(bReturn, bOpen);
    return bReturn;
}

bool UVK::SettingsWidgets::displayProjectSettings(std::string& name, std::string& ver, std::string& enginever, std::string& startupLevel, bool& bOpen)
{
    UVK_SETTINGS_WIDGET_BEGIN("Project Settings", ImGuiWindowFlags_None)
        UVK::ProjectSettingsWidget::displayProjectSettings(bReturn, name, ver, enginever, startupLevel, bOpen);
    return bReturn;
}

bool UVK::SettingsWidgets::displayEditorSettings(bool& bOpen, UVK::Editor& editor)
{
    UVK_SETTINGS_WIDGET_BEGIN("Editor Settings", ImGuiWindowFlags_None)
        UVK::EditorSettingsWidget::displayEditorSettingsWidget(bReturn, bOpen, editor);
    return bReturn;
}

#endif