// WindowSettings.cpp
// Last update 18/2/2022 by Madman10K
#include "WindowSettings.hpp"
#include "Core/Interfaces/WindowInterface.hpp"
#include "Core/Interfaces/SettingsManager.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

void UVK::WindowSettingsWidget::display(bool& bReturn, bool& bOpen)
{
    int arr[] = { (int)UVK::Window::windowSize().x, (int)UVK::Window::windowSize().y };

    ImGui::TextWrapped("DISCLAIMER: The editor needs to be reloaded for changes to appear!");

    ImGui::TextWrapped("Fullscreen");
    ImGui::SameLine();
    ImGui::Checkbox("##Fullscreen", &UVK::Window::fullscreen());

    ImGui::TextWrapped("Window Size");
    ImGui::SameLine();
    if (ImGui::InputScalarN("##Window Size", ImGuiDataType_S32, arr, 2) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Window Name");
    ImGui::SameLine();
    if (ImGui::InputText("##Window Name", &UVK::Window::name()) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Window Icon Location");
    ImGui::SameLine();
    if (ImGui::InputText("##Window Icon location", &UVK::Window::iconLocation()) || ImGui::IsItemActive())
        bReturn = true;

    UVK::Window::windowSize().x = (float)arr[0];
    UVK::Window::windowSize().y = (float)arr[1];

    if (ImGui::Button("Close"))
        bOpen = false;
    ImGui::SameLine();
    if (ImGui::Button("Save"))
        UVK::SettingsManager::saveWindowSettings();
    ImGui::EndPopup();
}