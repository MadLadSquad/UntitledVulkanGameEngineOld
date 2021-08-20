// Settings.cpp
// Last update 2/8/2021 by Madman10K
#include <GL/glew.h>
#include "Settings.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <Core/Global.hpp>
#include <Renderer/EditorUI/Style/Theme.hpp>
#include <Core/Interfaces/SettingsManager.hpp>

void Settings::displayWindow(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("Window Settings"))
        ImGui::OpenPopup("Window Settings");
    if (ImGui::BeginPopupModal("Window Settings", &bOpen))
    {
        int arr[] = { (int)UVK::Window::windowSize().x, (int)UVK::Window::windowSize().y };

        ImGui::TextWrapped("DISCLAIMER: The editor needs to be reloaded for changes to appear!");

        ImGui::TextWrapped("Fullscreen");
        ImGui::SameLine();
        ImGui::Checkbox("##Fullscreen", &UVK::Window::fullscreen());

        ImGui::TextWrapped("Window Size");
        ImGui::SameLine();
        ImGui::InputInt2("##Window Size", arr);

        ImGui::TextWrapped("Window Name");
        ImGui::SameLine();
        ImGui::InputText("##Window Name", &UVK::Window::name());

        ImGui::TextWrapped("Window Icon Location");
        ImGui::SameLine();
        ImGui::InputText("##Window Icon location", &UVK::Window::iconLocation());

        UVK::Window::windowSize().x = (float)arr[0];
        UVK::Window::windowSize().y = (float)arr[1];

        if (ImGui::Button("Close"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            UVK::SettingsManager::saveWindowSettings();
        }
        ImGui::EndPopup();
    }
}

void Settings::displayRenderer(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("Renderer Settings"))
        ImGui::OpenPopup("Renderer Settings");
    if (ImGui::BeginPopupModal("Renderer Settings", &bOpen))
    {
        ImGui::TextWrapped("DISCLAIMER: The editor needs to be reloaded for changes to appear!");

        ImGui::TextWrapped("Vulkan");
        ImGui::SameLine();
        ImGui::Checkbox("##Vulkan", &UVK::global.bUsesVulkan);

        ImGui::TextWrapped("Theme Location");
        ImGui::SameLine();
        ImGui::InputText("##Theme Location", &UVK::SettingsManager::getRendererSettings().themeLoc);

        if (ImGui::Button("Close"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            UVK::SettingsManager::saveRendererSettings();
        }
        ImGui::EndPopup();
    }
}

void Settings::displayKeybindEditor(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("Editor Keybinds"))
        ImGui::OpenPopup("Editor Keybinds");
    if (ImGui::BeginPopupModal("Editor Keybinds", &bOpen))
    {
        for (auto& a : UVK::InputActions::getActions())
        {
            if (a.name.find("editor-") != std::string::npos)
            {
                ImGui::TextWrapped("%s", a.name.c_str());

                ImGui::TextWrapped("Name");
                ImGui::SameLine();
                ImGui::InputText(static_cast<std::string>("##Name##" + a.name + std::to_string(a.keyCode)).c_str(), &a.name);

                int i = a.keyCode;

                ImGui::TextWrapped("Keycode");
                ImGui::SameLine();
                ImGui::InputInt("##Keycode", &i);
                a.keyCode = i;
                ImGui::Separator();
            }
        }

        if (ImGui::Button("Close"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            UVK::SettingsManager::saveEditorKeybindSettings();
        }
        ImGui::EndPopup();
    }
}

void Settings::displayKeybindGame(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("Game Keybinds"))
        ImGui::OpenPopup("Game Keybinds");
    if (ImGui::BeginPopupModal("Game Keybinds", &bOpen, ImGuiWindowFlags_MenuBar))
    {
        ImGui::BeginMenuBar();
        bool bDestroy = false;

        if (ImGui::MenuItem("+ Add Keybind##scn"))
        {
            UVK::InputAction action;
            static int newact = 0;
            action.name = "NewAction" + std::to_string(newact);
            action.keyCode = 0;

            UVK::InputActions::getActions().push_back(action);
            ++newact;
        }
        if (ImGui::MenuItem("- Remove Keybind##scn")) bDestroy = true;

        ImGui::EndMenuBar();

        for (int i = 0; i < UVK::InputActions::getActions().size(); i++)
        {
            if (UVK::InputActions::getActions()[i].name.find("editor-") == std::string::npos)
            {
                if (bDestroy)
                {
                    UVK::InputActions::getActions().erase(UVK::InputActions::getActions().begin() + i);
                    bDestroy = false;
                }
                else
                {
                    ImGui::TextWrapped("%s", UVK::InputActions::getActions()[i].name.c_str());

                    ImGui::TextWrapped("Name");
                    ImGui::SameLine();
                    ImGui::InputText(static_cast<std::string>("##Name##" + UVK::InputActions::getActions()[i].name + std::to_string(UVK::InputActions::getActions()[i].keyCode)).c_str(), &UVK::InputActions::getActions()[i].name);

                    int a = UVK::InputActions::getActions()[i].keyCode;
                    ImGui::TextWrapped("Keycode");
                    ImGui::SameLine();
                    ImGui::InputInt(static_cast<std::string>("##Keycode##" + UVK::InputActions::getActions()[i].name + std::to_string(UVK::InputActions::getActions()[i].keyCode)).c_str(), &a);
                    UVK::InputActions::getActions()[i].keyCode = a;
                    ImGui::Separator();
                }
            }
        }

        if (ImGui::Button("Close"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            UVK::SettingsManager::saveKeybindSettings();
        }
        ImGui::EndPopup();
    }
}

void Settings::displayThemeEditor(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("Theme Editor"))
        ImGui::OpenPopup("Theme Editor");
    if (ImGui::BeginPopupModal("Theme Editor", &bOpen))
    {
        auto& colours = ImGui::GetStyle().Colors;

        {
            float arr[] = { colours[ImGuiCol_Text].x, colours[ImGuiCol_Text].y, colours[ImGuiCol_Text].z, colours[ImGuiCol_Text].w };
            ImGui::TextWrapped("Text Colour");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Text Colour", arr);
            colours[ImGuiCol_Text].x = arr[0], colours[ImGuiCol_Text].y = arr[1], colours[ImGuiCol_Text].z = arr[2], colours[ImGuiCol_Text].w = arr[3];
        }

        {
            float windowBg[] = { colours[ImGuiCol_WindowBg].x, colours[ImGuiCol_WindowBg].y, colours[ImGuiCol_WindowBg].z, colours[ImGuiCol_WindowBg].w };
            ImGui::TextWrapped("Window Background");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Window Background", windowBg);
            colours[ImGuiCol_WindowBg].x = windowBg[0], colours[ImGuiCol_WindowBg].y = windowBg[1], colours[ImGuiCol_WindowBg].z = windowBg[2], colours[ImGuiCol_WindowBg].w = windowBg[3];
        }

        ImGui::Separator();

        {
            float header[] = { colours[ImGuiCol_Header].x, colours[ImGuiCol_Header].y, colours[ImGuiCol_Header].z, colours[ImGuiCol_Header].w };
            ImGui::TextWrapped("Header");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Header", header);
            colours[ImGuiCol_Header].x = header[0], colours[ImGuiCol_Header].y = header[1], colours[ImGuiCol_Header].z = header[2], colours[ImGuiCol_Header].w = header[3];
        }

        {
            float arr[] = { colours[ImGuiCol_HeaderHovered].x, colours[ImGuiCol_HeaderHovered].y, colours[ImGuiCol_HeaderHovered].z, colours[ImGuiCol_HeaderHovered].w };
            ImGui::TextWrapped("Header Hovered");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Header Hovered", arr);
            colours[ImGuiCol_HeaderHovered].x = arr[0], colours[ImGuiCol_HeaderHovered].y = arr[1], colours[ImGuiCol_HeaderHovered].z = arr[2], colours[ImGuiCol_HeaderHovered].w = arr[3];
        }

        {
            float arr[] = { colours[ImGuiCol_HeaderActive].x, colours[ImGuiCol_HeaderActive].y, colours[ImGuiCol_HeaderActive].z, colours[ImGuiCol_HeaderActive].w };
            ImGui::TextWrapped("Header Active");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Header Active", arr);
            colours[ImGuiCol_HeaderActive].x = arr[0], colours[ImGuiCol_HeaderActive].y = arr[1], colours[ImGuiCol_HeaderActive].z = arr[2], colours[ImGuiCol_HeaderActive].w = arr[3];
        }

        ImGui::Separator();

        {
            float header[] = { colours[ImGuiCol_Button].x, colours[ImGuiCol_Button].y, colours[ImGuiCol_Button].z, colours[ImGuiCol_Button].w };
            ImGui::TextWrapped("Button");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Button", header);
            colours[ImGuiCol_Button].x = header[0], colours[ImGuiCol_Button].y = header[1], colours[ImGuiCol_Button].z = header[2], colours[ImGuiCol_Button].w = header[3];
        }

        {
            float arr[] = { colours[ImGuiCol_ButtonHovered].x, colours[ImGuiCol_ButtonHovered].y, colours[ImGuiCol_ButtonHovered].z, colours[ImGuiCol_ButtonHovered].w };
            ImGui::TextWrapped("Button Hovered");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Button Hovered", arr);
            colours[ImGuiCol_ButtonHovered].x = arr[0], colours[ImGuiCol_ButtonHovered].y = arr[1], colours[ImGuiCol_ButtonHovered].z = arr[2], colours[ImGuiCol_ButtonHovered].w = arr[3];
        }

        {
            float arr[] = { colours[ImGuiCol_ButtonActive].x, colours[ImGuiCol_ButtonActive].y, colours[ImGuiCol_ButtonActive].z, colours[ImGuiCol_ButtonActive].w };
            ImGui::TextWrapped("Button Active");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Button Active", arr);
            colours[ImGuiCol_ButtonActive].x = arr[0], colours[ImGuiCol_ButtonActive].y = arr[1], colours[ImGuiCol_ButtonActive].z = arr[2], colours[ImGuiCol_ButtonActive].w = arr[3];
        }

        ImGui::Separator();

        {
            float header[] = { colours[ImGuiCol_FrameBg].x, colours[ImGuiCol_FrameBg].y, colours[ImGuiCol_FrameBg].z, colours[ImGuiCol_FrameBg].w };
            ImGui::TextWrapped("Frame");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Frame", header);
            colours[ImGuiCol_FrameBg].x = header[0], colours[ImGuiCol_FrameBg].y = header[1], colours[ImGuiCol_FrameBg].z = header[2], colours[ImGuiCol_FrameBg].w = header[3];
        }

        {
            float arr[] = { colours[ImGuiCol_FrameBgHovered].x, colours[ImGuiCol_FrameBgHovered].y, colours[ImGuiCol_FrameBgHovered].z, colours[ImGuiCol_FrameBgHovered].w };
            ImGui::TextWrapped("Frame Hovered");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Frame Hovered", arr);
            colours[ImGuiCol_FrameBgHovered].x = arr[0], colours[ImGuiCol_FrameBgHovered].y = arr[1], colours[ImGuiCol_FrameBgHovered].z = arr[2], colours[ImGuiCol_FrameBgHovered].w = arr[3];
        }

        {
            float arr[] = { colours[ImGuiCol_FrameBgActive].x, colours[ImGuiCol_FrameBgActive].y, colours[ImGuiCol_FrameBgActive].z, colours[ImGuiCol_FrameBgActive].w };
            ImGui::TextWrapped("Frame Active");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Frame Active", arr);
            colours[ImGuiCol_FrameBgActive].x = arr[0], colours[ImGuiCol_FrameBgActive].y = arr[1], colours[ImGuiCol_FrameBgActive].z = arr[2], colours[ImGuiCol_FrameBgActive].w = arr[3];
        }

        ImGui::Separator();

        {
            float header[] = { colours[ImGuiCol_Tab].x, colours[ImGuiCol_Tab].y, colours[ImGuiCol_Tab].z, colours[ImGuiCol_Tab].w };
            ImGui::TextWrapped("Tab");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Tab", header);
            colours[ImGuiCol_Tab].x = header[0], colours[ImGuiCol_Tab].y = header[1], colours[ImGuiCol_Tab].z = header[2], colours[ImGuiCol_Tab].w = header[3];
        }

        {
            float arr[] = { colours[ImGuiCol_TabHovered].x, colours[ImGuiCol_TabHovered].y, colours[ImGuiCol_TabHovered].z, colours[ImGuiCol_TabHovered].w };
            ImGui::TextWrapped("Tab Hovered");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Tab Hovered", arr);
            colours[ImGuiCol_TabHovered].x = arr[0], colours[ImGuiCol_TabHovered].y = arr[1], colours[ImGuiCol_TabHovered].z = arr[2], colours[ImGuiCol_TabHovered].w = arr[3];
        }

        {
            float arr[] = { colours[ImGuiCol_TabActive].x, colours[ImGuiCol_TabActive].y, colours[ImGuiCol_TabActive].z, colours[ImGuiCol_TabActive].w };
            ImGui::TextWrapped("Tab Active");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Tab Active", arr);
            colours[ImGuiCol_TabActive].x = arr[0], colours[ImGuiCol_TabActive].y = arr[1], colours[ImGuiCol_TabActive].z = arr[2], colours[ImGuiCol_TabActive].w = arr[3];
        }

        {
            float arr[] = { colours[ImGuiCol_TabUnfocused].x, colours[ImGuiCol_TabUnfocused].y, colours[ImGuiCol_TabUnfocused].z, colours[ImGuiCol_TabUnfocused].w };
            ImGui::TextWrapped("Tab Unfocused");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Tab Unfocused", arr);
            colours[ImGuiCol_TabUnfocused].x = arr[0], colours[ImGuiCol_TabUnfocused].y = arr[1], colours[ImGuiCol_TabUnfocused].z = arr[2], colours[ImGuiCol_TabUnfocused].w = arr[3];
        }

        {
            float arr[] = { colours[ImGuiCol_TabUnfocusedActive].x, colours[ImGuiCol_TabUnfocusedActive].y, colours[ImGuiCol_TabUnfocusedActive].z, colours[ImGuiCol_TabUnfocusedActive].w };
            ImGui::TextWrapped("Tab Unfocused Active");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Tab Unfocused Active", arr);
            colours[ImGuiCol_TabUnfocusedActive].x = arr[0], colours[ImGuiCol_TabUnfocusedActive].y = arr[1], colours[ImGuiCol_TabUnfocusedActive].z = arr[2], colours[ImGuiCol_TabUnfocusedActive].w = arr[3];
        }

        ImGui::Separator();

        {
            float arr[] = { colours[ImGuiCol_TitleBg].x, colours[ImGuiCol_TitleBg].y, colours[ImGuiCol_TitleBg].z, colours[ImGuiCol_TitleBg].w };
            ImGui::TextWrapped("Title Background");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Title Background", arr);
            colours[ImGuiCol_TitleBg].x = arr[0], colours[ImGuiCol_TitleBg].y = arr[1], colours[ImGuiCol_TitleBg].z = arr[2], colours[ImGuiCol_TitleBg].w = arr[3];
        }

        {
            float arr[] = { colours[ImGuiCol_TitleBgActive].x, colours[ImGuiCol_TitleBgActive].y, colours[ImGuiCol_TitleBgActive].z, colours[ImGuiCol_TitleBgActive].w };
            ImGui::TextWrapped("Title Background Active");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Title Background Active", arr);
            colours[ImGuiCol_TitleBgActive].x = arr[0], colours[ImGuiCol_TitleBgActive].y = arr[1], colours[ImGuiCol_TitleBgActive].z = arr[2], colours[ImGuiCol_TitleBgActive].w = arr[3];
        }

        {
            float arr[] = { colours[ImGuiCol_TitleBgCollapsed].x, colours[ImGuiCol_TitleBgCollapsed].y, colours[ImGuiCol_TitleBgCollapsed].z, colours[ImGuiCol_TitleBgCollapsed].w };
            ImGui::TextWrapped("Title Background Collapsed");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Title Background Collapsed", arr);
            colours[ImGuiCol_TitleBgCollapsed].x = arr[0], colours[ImGuiCol_TitleBgCollapsed].y = arr[1], colours[ImGuiCol_TitleBgCollapsed].z = arr[2], colours[ImGuiCol_TitleBgCollapsed].w = arr[3];
        }

        ImGui::Separator();

        {
            float arr[] = { colours[ImGuiCol_MenuBarBg].x, colours[ImGuiCol_MenuBarBg].y, colours[ImGuiCol_MenuBarBg].z, colours[ImGuiCol_MenuBarBg].w };
            ImGui::TextWrapped("Menubar Background");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Menubar Background", arr);
            colours[ImGuiCol_MenuBarBg].x = arr[0], colours[ImGuiCol_MenuBarBg].y = arr[1], colours[ImGuiCol_MenuBarBg].z = arr[2], colours[ImGuiCol_MenuBarBg].w = arr[3];
        }

        {
            float arr[] = { colours[ImGuiCol_PopupBg].x, colours[ImGuiCol_PopupBg].y, colours[ImGuiCol_PopupBg].z, colours[ImGuiCol_PopupBg].w };
            ImGui::TextWrapped("Popup Background");
            ImGui::SameLine();
            ImGui::ColorEdit4("##Popup Background", arr);
            colours[ImGuiCol_PopupBg].x = arr[0], colours[ImGuiCol_PopupBg].y = arr[1], colours[ImGuiCol_PopupBg].z = arr[2], colours[ImGuiCol_PopupBg].w = arr[3];
        }

        ImGui::Separator();

        static std::string fontLoc;
        static std::string outName;
        static int fontSize = 12;

        ImGui::TextWrapped("Font Location: Content/");
        ImGui::SameLine();
        ImGui::InputText("##Font Location", &fontLoc);

        ImGui::TextWrapped("Font Size");
        ImGui::SameLine();
        ImGui::InputInt("##Font Size", &fontSize);

        ImGui::TextWrapped("Output Location: Config/Settings/");
        ImGui::SameLine();
        ImGui::InputText("##Output Location", &outName);
        ImGui::SameLine();
        ImGui::TextWrapped(".uvktheme");

        if (ImGui::Button("Close"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
#ifdef DEVELOPMENT
            UVK::EditorTheme::save(static_cast<std::string>("../Config/Settings/" + outName + ".uvktheme").c_str(), static_cast<std::string>("../Content/" + fontLoc).c_str(), fontSize);
#endif
        }
        ImGui::EndPopup();
    }
}

void Settings::displayProjectSettings(std::string& name, std::string& ver, std::string& enginever, std::string& startupLevel, bool& bOpen)
{
    if (!ImGui::IsPopupOpen("Project Settings"))
        ImGui::OpenPopup("Project Settings");
    if (ImGui::BeginPopupModal("Project Settings", &bOpen))
    {
        ImGui::TextWrapped("Project Name");
        ImGui::SameLine();
        ImGui::InputText("##Project Name", &name);

        ImGui::TextWrapped("Project Version");
        ImGui::SameLine();
        ImGui::InputText("##Project Version", &ver);

        ImGui::TextWrapped("Engine Version");
        ImGui::SameLine();
        ImGui::InputText("##Engine Version", &enginever);

        ImGui::TextWrapped("Startup Level Name");
        ImGui::SameLine();
        ImGui::InputText("##Startup Level Name", &startupLevel);
        ImGui::SameLine();
        ImGui::TextWrapped(".uvklevel");

        ImGui::TextWrapped("If you click \"Save\" your project's generated files will be regenerated!");

        if (ImGui::Button("Close"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            YAML::Emitter o;
            o << YAML::BeginMap << YAML::Key << "name" << YAML::Value << name;
            o << YAML::Key << "startup-level" << YAML::Value << startupLevel;
            o << YAML::Key << "version" << YAML::Value << ver;
            o << YAML::Key << "engine-version" << YAML::Value << enginever << YAML::EndMap;

            std::ofstream out("../uvproj.yaml");
            out << o.c_str();
            out.close();

            static int lnt;
#ifndef _WIN32
            lnt = system("cd ../UVKBuildTool/build && ./UVKBuildTool --generate && cd ../../");
#else
            lnt = system("cd ../UVKBuildTool/build && UVKBuildTool.exe --generate && cd ../../");
#endif
            if (lnt)
            {

            }
        }
        ImGui::EndPopup();
    }
}