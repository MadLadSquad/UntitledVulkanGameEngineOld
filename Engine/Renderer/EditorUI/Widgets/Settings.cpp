// Settings.cpp
// Last update 6/7/2021 by Madman10K
#include <GL/glew.h>
#include "Settings.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <Core/Global.hpp>
#include <Renderer/EditorUI/Style/Theme.hpp>

void Settings::displayWindow(bool& bOpen)
{
    ImGui::Begin("Window Settings", &bOpen);

    int arr[] = { (int)UVK::global.window.data().size.x, (int)UVK::global.window.data().size.y };

    ImGui::Text("DISCLAIMER: The editor needs to be reloaded for changes to appear!");
    ImGui::Checkbox("Fullscreen", &UVK::global.window.data().fullscreen);
    ImGui::InputInt2("Window Size", arr);
    ImGui::InputText("Window Name", &UVK::global.window.data().name);
    ImGui::InputText("Window Icon location", &UVK::global.window.data().image);

    UVK::global.window.data().size.x = (float)arr[0];
    UVK::global.window.data().size.y = (float)arr[1];

    if (ImGui::Button("Close"))
    {
        bOpen = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        UVK::global.window.dumpConfig();
    }
    ImGui::End();
}

void Settings::displayRenderer(bool& bOpen)
{
    ImGui::Begin("Renderer Settings", &bOpen);

    ImGui::Text("DISCLAIMER: The editor needs to be reloaded for changes to appear!");
    ImGui::Checkbox("Vulkan", &UVK::global.rendererSettings.bVulkan);
    ImGui::InputText("Theme Location", &UVK::global.rendererSettings.themeLoc);

    if (ImGui::Button("Close"))
    {
        bOpen = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        UVK::global.rendererSettings.saveSettings();
    }
    ImGui::End();
}

void Settings::displayKeybindEditor(bool& bOpen)
{
    ImGui::Begin("Editor Keybinds", &bOpen);

    for (auto& a : UVK::global.getActions())
    {
        if (a.name.find("editor-") != std::string::npos)
        {
            ImGui::Separator();
            ImGui::Text("%s", a.name.c_str());
            ImGui::InputText(static_cast<std::string>("Name##" + a.name + std::to_string(a.keyCode)).c_str(), &a.name);

            int i = a.keyCode;
            ImGui::InputInt("Keycode", &i);
            a.keyCode = i;
        }
    }

    ImGui::Separator();
    if (ImGui::Button("Close"))
    {
        bOpen = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        UVK::global.window.saveEditorKeybinds();
    }
    ImGui::End();
}

void Settings::displayKeybindGame(bool &bOpen)
{
    ImGui::Begin("Game Keybinds", &bOpen, ImGuiWindowFlags_MenuBar);

    ImGui::BeginMenuBar();
    bool bDestroy = false;
    static int newact;
    if (ImGui::MenuItem("+ Add Keybind##scn"))
    {
        UVK::InputAction action;
        action.name = "NewAction" + std::to_string(newact);
        action.keyCode = 0;

        UVK::global.getActions().push_back(action);
        ++newact;
    }
    if (ImGui::MenuItem("- Remove Keybind##scn")) bDestroy = true;

    ImGui::EndMenuBar();

    for (int a = 0; a < UVK::global.getActions().size(); a++)
    {
        if (UVK::global.getActions()[a].name.find("editor-") == std::string::npos)
        {
            if (bDestroy)
            {
                UVK::global.getActions().erase(UVK::global.getActions().begin() + a);
                bDestroy = false;
            }
            else
            {
                ImGui::Separator();
                ImGui::Text("%s", UVK::global.getActions()[a].name.c_str());
                ImGui::InputText(static_cast<std::string>("Name##" + UVK::global.getActions()[a].name + std::to_string(UVK::global.getActions()[a].keyCode)).c_str(), &UVK::global.getActions()[a].name);

                int i = UVK::global.getActions()[a].keyCode;
                ImGui::InputInt(static_cast<std::string>("Keycode##" + UVK::global.getActions()[a].name + std::to_string(UVK::global.getActions()[a].keyCode)).c_str(), &i);
                UVK::global.getActions()[a].keyCode = i;
            }
        }
    }

    ImGui::Separator();

    if (ImGui::Button("Close"))
    {
        bOpen = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        UVK::Window::saveGameKeybinds();
    }
    ImGui::End();
}

void Settings::displayThemeEditor(bool& bOpen)
{
    ImGui::Begin("Theme Editor", &bOpen);
    auto& colours = ImGui::GetStyle().Colors;

    {
        float arr[] = { colours[ImGuiCol_Text].x, colours[ImGuiCol_Text].y, colours[ImGuiCol_Text].z, colours[ImGuiCol_Text].w };
        ImGui::ColorEdit4("Text Colour", arr);
        colours[ImGuiCol_Text].x = arr[0], colours[ImGuiCol_Text].y = arr[1], colours[ImGuiCol_Text].z = arr[2], colours[ImGuiCol_Text].w = arr[3];
    }

    {
        float windowBg[] = { colours[ImGuiCol_WindowBg].x, colours[ImGuiCol_WindowBg].y, colours[ImGuiCol_WindowBg].z, colours[ImGuiCol_WindowBg].w };
        ImGui::ColorEdit4("Window Background", windowBg);
        colours[ImGuiCol_WindowBg].x = windowBg[0], colours[ImGuiCol_WindowBg].y = windowBg[1], colours[ImGuiCol_WindowBg].z = windowBg[2], colours[ImGuiCol_WindowBg].w = windowBg[3];
    }

    ImGui::Separator();

    {
        float header[] = { colours[ImGuiCol_Header].x, colours[ImGuiCol_Header].y, colours[ImGuiCol_Header].z, colours[ImGuiCol_Header].w };
        ImGui::ColorEdit4("Header", header);
        colours[ImGuiCol_Header].x = header[0], colours[ImGuiCol_Header].y = header[1], colours[ImGuiCol_Header].z = header[2], colours[ImGuiCol_Header].w = header[3];
    }

    {
        float arr[] = { colours[ImGuiCol_HeaderHovered].x, colours[ImGuiCol_HeaderHovered].y, colours[ImGuiCol_HeaderHovered].z, colours[ImGuiCol_HeaderHovered].w };
        ImGui::ColorEdit4("Header Hovered", arr);
        colours[ImGuiCol_HeaderHovered].x = arr[0], colours[ImGuiCol_HeaderHovered].y = arr[1], colours[ImGuiCol_HeaderHovered].z = arr[2], colours[ImGuiCol_HeaderHovered].w = arr[3];
    }

    {
        float arr[] = { colours[ImGuiCol_HeaderActive].x, colours[ImGuiCol_HeaderActive].y, colours[ImGuiCol_HeaderActive].z, colours[ImGuiCol_HeaderActive].w };
        ImGui::ColorEdit4("Header Active", arr);
        colours[ImGuiCol_HeaderActive].x = arr[0], colours[ImGuiCol_HeaderActive].y = arr[1], colours[ImGuiCol_HeaderActive].z = arr[2], colours[ImGuiCol_HeaderActive].w = arr[3];
    }

    ImGui::Separator();

    {
        float header[] = { colours[ImGuiCol_Button].x, colours[ImGuiCol_Button].y, colours[ImGuiCol_Button].z, colours[ImGuiCol_Button].w };
        ImGui::ColorEdit4("Button", header);
        colours[ImGuiCol_Button].x = header[0], colours[ImGuiCol_Button].y = header[1], colours[ImGuiCol_Button].z = header[2], colours[ImGuiCol_Button].w = header[3];
    }

    {
        float arr[] = { colours[ImGuiCol_ButtonHovered].x, colours[ImGuiCol_ButtonHovered].y, colours[ImGuiCol_ButtonHovered].z, colours[ImGuiCol_ButtonHovered].w };
        ImGui::ColorEdit4("Button Hovered", arr);
        colours[ImGuiCol_ButtonHovered].x = arr[0], colours[ImGuiCol_ButtonHovered].y = arr[1], colours[ImGuiCol_ButtonHovered].z = arr[2], colours[ImGuiCol_ButtonHovered].w = arr[3];
    }

    {
        float arr[] = { colours[ImGuiCol_ButtonActive].x, colours[ImGuiCol_ButtonActive].y, colours[ImGuiCol_ButtonActive].z, colours[ImGuiCol_ButtonActive].w };
        ImGui::ColorEdit4("Button Active", arr);
        colours[ImGuiCol_ButtonActive].x = arr[0], colours[ImGuiCol_ButtonActive].y = arr[1], colours[ImGuiCol_ButtonActive].z = arr[2], colours[ImGuiCol_ButtonActive].w = arr[3];
    }

    ImGui::Separator();

    {
        float header[] = { colours[ImGuiCol_FrameBg].x, colours[ImGuiCol_FrameBg].y, colours[ImGuiCol_FrameBg].z, colours[ImGuiCol_FrameBg].w };
        ImGui::ColorEdit4("Frame", header);
        colours[ImGuiCol_FrameBg].x = header[0], colours[ImGuiCol_FrameBg].y = header[1], colours[ImGuiCol_FrameBg].z = header[2], colours[ImGuiCol_FrameBg].w = header[3];
    }

    {
        float arr[] = { colours[ImGuiCol_FrameBgHovered].x, colours[ImGuiCol_FrameBgHovered].y, colours[ImGuiCol_FrameBgHovered].z, colours[ImGuiCol_FrameBgHovered].w };
        ImGui::ColorEdit4("Frame Hovered", arr);
        colours[ImGuiCol_FrameBgHovered].x = arr[0], colours[ImGuiCol_FrameBgHovered].y = arr[1], colours[ImGuiCol_FrameBgHovered].z = arr[2], colours[ImGuiCol_FrameBgHovered].w = arr[3];
    }

    {
        float arr[] = { colours[ImGuiCol_FrameBgActive].x, colours[ImGuiCol_FrameBgActive].y, colours[ImGuiCol_FrameBgActive].z, colours[ImGuiCol_FrameBgActive].w };
        ImGui::ColorEdit4("Frame Active", arr);
        colours[ImGuiCol_FrameBgActive].x = arr[0], colours[ImGuiCol_FrameBgActive].y = arr[1], colours[ImGuiCol_FrameBgActive].z = arr[2], colours[ImGuiCol_FrameBgActive].w = arr[3];
    }

    ImGui::Separator();

    {
        float header[] = { colours[ImGuiCol_Tab].x, colours[ImGuiCol_Tab].y, colours[ImGuiCol_Tab].z, colours[ImGuiCol_Tab].w };
        ImGui::ColorEdit4("Tab", header);
        colours[ImGuiCol_Tab].x = header[0], colours[ImGuiCol_Tab].y = header[1], colours[ImGuiCol_Tab].z = header[2], colours[ImGuiCol_Tab].w = header[3];
    }

    {
        float arr[] = { colours[ImGuiCol_TabHovered].x, colours[ImGuiCol_TabHovered].y, colours[ImGuiCol_TabHovered].z, colours[ImGuiCol_TabHovered].w };
        ImGui::ColorEdit4("Tab Hovered", arr);
        colours[ImGuiCol_TabHovered].x = arr[0], colours[ImGuiCol_TabHovered].y = arr[1], colours[ImGuiCol_TabHovered].z = arr[2], colours[ImGuiCol_TabHovered].w = arr[3];
    }

    {
        float arr[] = { colours[ImGuiCol_TabActive].x, colours[ImGuiCol_TabActive].y, colours[ImGuiCol_TabActive].z, colours[ImGuiCol_TabActive].w };
        ImGui::ColorEdit4("Tab Active", arr);
        colours[ImGuiCol_TabActive].x = arr[0], colours[ImGuiCol_TabActive].y = arr[1], colours[ImGuiCol_TabActive].z = arr[2], colours[ImGuiCol_TabActive].w = arr[3];
    }

    {
        float arr[] = { colours[ImGuiCol_TabUnfocused].x, colours[ImGuiCol_TabUnfocused].y, colours[ImGuiCol_TabUnfocused].z, colours[ImGuiCol_TabUnfocused].w };
        ImGui::ColorEdit4("Tab Unfocused", arr);
        colours[ImGuiCol_TabUnfocused].x = arr[0], colours[ImGuiCol_TabUnfocused].y = arr[1], colours[ImGuiCol_TabUnfocused].z = arr[2], colours[ImGuiCol_TabUnfocused].w = arr[3];
    }

    {
        float arr[] = { colours[ImGuiCol_TabUnfocusedActive].x, colours[ImGuiCol_TabUnfocusedActive].y, colours[ImGuiCol_TabUnfocusedActive].z, colours[ImGuiCol_TabUnfocusedActive].w };
        ImGui::ColorEdit4("Tab Unfocused Active", arr);
        colours[ImGuiCol_TabUnfocusedActive].x = arr[0], colours[ImGuiCol_TabUnfocusedActive].y = arr[1], colours[ImGuiCol_TabUnfocusedActive].z = arr[2], colours[ImGuiCol_TabUnfocusedActive].w = arr[3];
    }

    ImGui::Separator();

    {
        float arr[] = { colours[ImGuiCol_TitleBg].x, colours[ImGuiCol_TitleBg].y, colours[ImGuiCol_TitleBg].z, colours[ImGuiCol_TitleBg].w };
        ImGui::ColorEdit4("Title Background", arr);
        colours[ImGuiCol_TitleBg].x = arr[0], colours[ImGuiCol_TitleBg].y = arr[1], colours[ImGuiCol_TitleBg].z = arr[2], colours[ImGuiCol_TitleBg].w = arr[3];
    }

    {
        float arr[] = { colours[ImGuiCol_TitleBgActive].x, colours[ImGuiCol_TitleBgActive].y, colours[ImGuiCol_TitleBgActive].z, colours[ImGuiCol_TitleBgActive].w };
        ImGui::ColorEdit4("Title Background Active", arr);
        colours[ImGuiCol_TitleBgActive].x = arr[0], colours[ImGuiCol_TitleBgActive].y = arr[1], colours[ImGuiCol_TitleBgActive].z = arr[2], colours[ImGuiCol_TitleBgActive].w = arr[3];
    }

    {
        float arr[] = { colours[ImGuiCol_TitleBgCollapsed].x, colours[ImGuiCol_TitleBgCollapsed].y, colours[ImGuiCol_TitleBgCollapsed].z, colours[ImGuiCol_TitleBgCollapsed].w };
        ImGui::ColorEdit4("Title Background Collapsed", arr);
        colours[ImGuiCol_TitleBgCollapsed].x = arr[0], colours[ImGuiCol_TitleBgCollapsed].y = arr[1], colours[ImGuiCol_TitleBgCollapsed].z = arr[2], colours[ImGuiCol_TitleBgCollapsed].w = arr[3];
    }

    ImGui::Separator();

    {
        float arr[] = { colours[ImGuiCol_MenuBarBg].x, colours[ImGuiCol_MenuBarBg].y, colours[ImGuiCol_MenuBarBg].z, colours[ImGuiCol_MenuBarBg].w };
        ImGui::ColorEdit4("Menubar Background", arr);
        colours[ImGuiCol_MenuBarBg].x = arr[0], colours[ImGuiCol_MenuBarBg].y = arr[1], colours[ImGuiCol_MenuBarBg].z = arr[2], colours[ImGuiCol_MenuBarBg].w = arr[3];
    }

    {
        float arr[] = { colours[ImGuiCol_PopupBg].x, colours[ImGuiCol_PopupBg].y, colours[ImGuiCol_PopupBg].z, colours[ImGuiCol_PopupBg].w };
        ImGui::ColorEdit4("Popup Background", arr);
        colours[ImGuiCol_PopupBg].x = arr[0], colours[ImGuiCol_PopupBg].y = arr[1], colours[ImGuiCol_PopupBg].z = arr[2], colours[ImGuiCol_PopupBg].w = arr[3];
    }

    ImGui::Separator();

    static std::string fontLoc;
    static std::string outName;
    static int fontSize = 12;

    ImGui::InputTextWithHint("Font Location", "Starts from the Content folder", &fontLoc);
    ImGui::InputInt("Font Size", &fontSize);
    ImGui::InputTextWithHint("Output Location", "Starts from the Config folder", &outName);

    if (ImGui::Button("Close"))
    {
        bOpen = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        UVK::EditorTheme::save(static_cast<std::string>("../Config/" + outName).c_str(), static_cast<std::string>("../Content/" + fontLoc).c_str(), fontSize);
    }
    ImGui::End();
}