// Settings.cpp
// Last update 2/9/2021 by Madman10K
#include "Settings.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <Core/Global.hpp>
#include <Renderer/EditorUI/Style/Theme.hpp>
#include <Core/Interfaces/SettingsManager.hpp>
#include <Renderer/Renderer.hpp>

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

        static bool bVulkan = false;
        static bool first = false;

        if (!first)
        {
            bVulkan = UVK::global.bUsesVulkan;
            first = true;
        }

        ImGui::TextWrapped("Vulkan");
        ImGui::SameLine();
        ImGui::Checkbox("##Vulkan", &bVulkan);

        ImGui::TextWrapped("Theme Location");
        ImGui::SameLine();
        ImGui::InputText("##Theme Location", &UVK::SettingsManager::getRendererSettings().themeLoc);

        ImGui::TextWrapped("V-Sync");
        ImGui::SameLine();
        ImGui::Checkbox("##V-Sync", &UVK::Renderer::getVSync());

        ImGui::TextWrapped("Immediate frame display");
        ImGui::SameLine();
        ImGui::Checkbox("##V-Sync immediate", &UVK::Renderer::getImmediateRender());

        if (ImGui::Button("Close"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            bool temp = UVK::global.bUsesVulkan;
            UVK::global.bUsesVulkan = bVulkan;
            UVK::SettingsManager::saveRendererSettings();
            UVK::global.bUsesVulkan = temp;
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
        int i = 0;
        for (auto& a : UVK::InputActions::getActions())
        {
            if (a.name.find("editor-") != std::string::npos)
            {
                ImGui::TextWrapped("%s", a.name.c_str());

                ImGui::TextWrapped("Name");
                ImGui::SameLine();
                ImGui::InputText(static_cast<std::string>("##Name##" + a.name + std::to_string(a.keyCode)).c_str(), &a.name);

                ImGui::TextWrapped("Keycode");
                ImGui::SameLine();
                showKeySelect(static_cast<std::string>("##Name##" + a.name + std::to_string(a.keyCode) + std::to_string(i)).c_str(), a.keyCode);
                ImGui::Separator();
                i++;
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

        int j = 0;
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

                    ImGui::TextWrapped("Keycode");
                    ImGui::SameLine();
                    showKeySelect(static_cast<std::string>("##Keycode##" + UVK::InputActions::getActions()[i].name + std::to_string(UVK::InputActions::getActions()[i].keyCode) + std::to_string(j)).c_str(), UVK::InputActions::getActions()[i].keyCode);
                    ImGui::Separator();
                    j++;
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

void Settings::showKeySelect(const char* name, uint16_t& key)
{
    static std::string text;
    switch (key)
    {
    case Keys::UnknownKey:
        text = "Unknown Key";
        break;
    case Keys::Space:
        text = "Space";
        break;
    case Keys::Apostrophe:
        text = "Apostrophe";
        break;
    case Keys::Comma:
        text = "Comma";
        break;
    case Keys::Minus:
        text = "Minus";
        break;
    case Keys::Period:
        text = "Period";
        break;
    case Keys::Slash:
        text = "Slash";
        break;
    case Keys::Zero:
        text = "Zero";
        break;
    case Keys::One:
        text = "One";
        break;
    case Keys::Two:
        text = "Two";
        break;
    case Keys::Three:
        text = "Three";
        break;
    case Keys::Four:
        text = "Four";
        break;
    case Keys::Five:
        text = "Five";
        break;
    case Keys::Six:
        text = "Six";
        break;
    case Keys::Seven:
        text = "Seven";
        break;
    case Keys::Eight:
        text = "Eight";
        break;
    case Keys::Nine:
        text = "Nine";
        break;
    case Keys::Semicolon:
        text = "Semicolon";
        break;
    case Keys::Equal:
        text = "Equal";
        break;
    case Keys::A:
        text = "A";
        break;
    case Keys::B:
        text = "B";
        break;
    case Keys::C:
        text = "C";
        break;
    case Keys::D:
        text = "D";
        break;
    case Keys::E:
        text = "E";
        break;
    case Keys::F:
        text = "F";
        break;
    case Keys::G:
        text = "G";
        break;
    case Keys::H:
        text = "H";
        break;
    case Keys::I:
        text = "I";
        break;
    case Keys::J:
        text = "J";
        break;
    case Keys::K:
        text = "K";
        break;
    case Keys::L:
        text = "L";
        break;
    case Keys::M:
        text = "M";
        break;
    case Keys::N:
        text = "N";
        break;
    case Keys::O:
        text = "O";
        break;
    case Keys::P:
        text = "P";
        break;
    case Keys::Q:
        text = "Q";
        break;
    case Keys::R:
        text = "R";
        break;
    case Keys::S:
        text = "S";
        break;
    case Keys::T:
        text = "T";
        break;
    case Keys::U:
        text = "U";
        break;
    case Keys::V:
        text = "V";
        break;
    case Keys::W:
        text = "W";
        break;
    case Keys::X:
        text = "X";
        break;
    case Keys::Y:
        text = "Y";
        break;
    case Keys::Z:
        text = "Z";
        break;
    case Keys::LeftBracket:
        text = "Left Bracket";
        break;
    case Keys::Backslash:
        text = "Backslash";
        break;
    case Keys::RightBracket:
        text = "Right Bracket";
        break;
    case Keys::GraveAccent:
        text = "GraveAccent";
        break;
    case Keys::WorldOne:
        text = "World One";
        break;
    case Keys::WorldTwo:
        text = "World Two";
        break;
    case Keys::Escape:
        text = "Escape";
        break;
    case Keys::Enter:
        text = "Enter";
        break;
    case Keys::Tab:
        text = "Tab";
        break;
    case Keys::Backspace:
        text = "Backspace";
        break;
    case Keys::Insert:
        text = "Insert";
        break;
    case Keys::Delete:
        text = "Delete";
        break;
    case Keys::RightArrow:
        text = "Right Arrow";
        break;
    case Keys::LeftArrow:
        text = "Left Arrow";
        break;
    case Keys::DownArrow:
        text = "Down Arrow";
        break;
    case Keys::UpArrow:
        text = "Up Arrow";
        break;
    case Keys::PageUp:
        text = "Page Up";
        break;
    case Keys::PageDown:
        text = "Page Down";
        break;
    case Keys::Home:
        text = "World Two";
        break;
    case Keys::End:
        text = "End";
        break;
    case Keys::CapsLock:
        text = "Caps Lock";
        break;
    case Keys::ScrollLock:
        text = "Scroll Lock";
        break;
    case Keys::NumLock:
        text = "Num Lock";
        break;
    case Keys::PrintScreen:
        text = "Print Screen";
        break;
    case Keys::Pause:
        text = "Pause";
        break;
    case Keys::F1:
        text = "F1";
        break;
    case Keys::F2:
        text = "F2";
        break;
    case Keys::F3:
        text = "F3";
        break;
    case Keys::F4:
        text = "F4";
        break;
    case Keys::F5:
        text = "F5";
        break;
    case Keys::F6:
        text = "F6";
        break;
    case Keys::F7:
        text = "F7";
        break;
    case Keys::F8:
        text = "F8";
        break;
    case Keys::F9:
        text = "F9";
        break;
    case Keys::F10:
        text = "F10";
        break;
    case Keys::F11:
        text = "F11";
        break;
    case Keys::F12:
        text = "F12";
        break;
    case Keys::F13:
        text = "F13";
        break;
    case Keys::F14:
        text = "F14";
        break;
    case Keys::F15:
        text = "F15";
        break;
    case Keys::F16:
        text = "F16";
        break;
    case Keys::F17:
        text = "F17";
        break;
    case Keys::F18:
        text = "F18";
        break;
    case Keys::F19:
        text = "F19";
        break;
    case Keys::F20:
        text = "F20";
        break;
    case Keys::F21:
        text = "F21";
        break;
    case Keys::F22:
        text = "F22";
        break;
    case Keys::F23:
        text = "F23";
        break;
    case Keys::F24:
        text = "F24";
        break;
    case Keys::F25:
        text = "F25";
        break;
    case Keys::NumPadZero:
        text = "Numpad Zero";
        break;
    case Keys::NumPadOne:
        text = "Numpad One";
        break;
    case Keys::NumPadTwo:
        text = "Numpad Two";
        break;
    case Keys::NumPadThree:
        text = "Numpad Three";
        break;
    case Keys::NumPadFour:
        text = "Numpad Four";
        break;
    case Keys::NumPadFive:
        text = "Numpad Five";
        break;
    case Keys::NumPadSix:
        text = "Numpad Six";
        break;
    case Keys::NumPadSeven:
        text = "Numpad Seven";
        break;
    case Keys::NumPadEight:
        text = "Numpad Eight";
        break;
    case Keys::NumPadNine:
        text = "Numpad Nine";
        break;
    case Keys::NumPadDecimal:
        text = "Numpad Decimal";
        break;
    case Keys::NumPadDivide:
        text = "Numpad Divide";
        break;
    case Keys::NumPadMultiply:
        text = "Numpad Multiply";
        break;
    case Keys::NumPadSubtract:
        text = "Numpad Subtract";
        break;
    case Keys::NumPadAdd:
        text = "Numpad Add";
        break;
    case Keys::NumPadEnter:
        text = "Numpad Enter";
        break;
    case Keys::NumPadEqual:
        text = "Numpad Equal";
        break;
    case Keys::LeftShift:
        text = "Left Shift";
        break;
    case Keys::LeftAlt:
        text = "Left Alt";
        break;
    case Keys::LeftControl:
        text = "Left Control";
        break;
    case Keys::LeftSuper:
        text = "Left Super/CMD/Windows";
        break;
    case Keys::RightShift:
        text = "Right Shift";
        break;
    case Keys::RightControl:
        text = "Right Control";
        break;
    case Keys::RightAlt:
        text = "Right Alt";
        break;
    case Keys::RightSuper:
        text = "Right Super/CMD/Windows";
        break;
    case Keys::Menu:
        text = "Menu";
        break;
    case Keys::MouseButtonLeft:
        text = "Mouse Button 1/Left";
        break;
    case Keys::MouseButtonRight:
        text = "Mouse Button 2/Right";
        break;
    case Keys::MouseButtonMiddle:
        text = "Mouse Button 3/Middle";
        break;
    case Keys::MouseButton4:
        text = "Mouse Button 4";
        break;
    case Keys::MouseButton5:
        text = "Mouse Button 5";
        break;
    case Keys::MouseButton6:
        text = "Mouse Button 6";
        break;
    case Keys::MouseButton7:
        text = "Mouse Button 7";
        break;
    case Keys::MouseButton8:
        text = "Mouse Button 8/Last";
        break;
    default:
        text = "Unknown Key";
        break;
    }

    if (ImGui::BeginCombo(name, text.c_str()))
    {
        if (ImGui::MenuItem("Unknown Key")) key = Keys::UnknownKey;
        if (ImGui::MenuItem("Space")) key = Keys::Space;
        if (ImGui::MenuItem("Apostrophe")) key = Keys::Apostrophe;
        if (ImGui::MenuItem("Comma")) key = Keys::Comma;
        if (ImGui::MenuItem("Minus")) key = Keys::Minus;
        if (ImGui::MenuItem("Period")) key = Keys::Period;
        if (ImGui::MenuItem("Slash")) key = Keys::Slash;
        if (ImGui::MenuItem("Zero")) key = Keys::Zero;
        if (ImGui::MenuItem("One")) key = Keys::One;
        if (ImGui::MenuItem("Two")) key = Keys::Two;
        if (ImGui::MenuItem("Three")) key = Keys::Three;
        if (ImGui::MenuItem("Four")) key = Keys::Four;
        if (ImGui::MenuItem("Five")) key = Keys::Five;
        if (ImGui::MenuItem("Six")) key = Keys::Six;
        if (ImGui::MenuItem("Seven")) key = Keys::Seven;
        if (ImGui::MenuItem("Eight")) key = Keys::Eight;
        if (ImGui::MenuItem("Nine")) key = Keys::Nine;
        if (ImGui::MenuItem("Semicolon")) key = Keys::Semicolon;
        if (ImGui::MenuItem("Equal")) key = Keys::Equal;

        ImGui::Separator();

        if (ImGui::MenuItem("A")) key = Keys::A;
        if (ImGui::MenuItem("B")) key = Keys::B;
        if (ImGui::MenuItem("C")) key = Keys::C;
        if (ImGui::MenuItem("D")) key = Keys::D;
        if (ImGui::MenuItem("E")) key = Keys::E;
        if (ImGui::MenuItem("F")) key = Keys::F;
        if (ImGui::MenuItem("G")) key = Keys::G;
        if (ImGui::MenuItem("H")) key = Keys::H;
        if (ImGui::MenuItem("I")) key = Keys::I;
        if (ImGui::MenuItem("J")) key = Keys::J;
        if (ImGui::MenuItem("K")) key = Keys::K;
        if (ImGui::MenuItem("L")) key = Keys::L;
        if (ImGui::MenuItem("M")) key = Keys::M;
        if (ImGui::MenuItem("N")) key = Keys::N;
        if (ImGui::MenuItem("O")) key = Keys::O;
        if (ImGui::MenuItem("P")) key = Keys::P;
        if (ImGui::MenuItem("Q")) key = Keys::Q;
        if (ImGui::MenuItem("R")) key = Keys::R;
        if (ImGui::MenuItem("S")) key = Keys::S;
        if (ImGui::MenuItem("T")) key = Keys::T;
        if (ImGui::MenuItem("U")) key = Keys::U;
        if (ImGui::MenuItem("V")) key = Keys::V;
        if (ImGui::MenuItem("W")) key = Keys::W;
        if (ImGui::MenuItem("X")) key = Keys::X;
        if (ImGui::MenuItem("Y")) key = Keys::Y;
        if (ImGui::MenuItem("Z")) key = Keys::Z;

        ImGui::Separator();

        if (ImGui::MenuItem("Left Bracket")) key = Keys::LeftBracket;
        if (ImGui::MenuItem("Backslash")) key = Keys::Backslash;
        if (ImGui::MenuItem("Right Bracket")) key = Keys::RightBracket;
        if (ImGui::MenuItem("Grave Accent")) key = Keys::GraveAccent;
        if (ImGui::MenuItem("World One")) key = Keys::WorldOne;
        if (ImGui::MenuItem("World Two")) key = Keys::WorldTwo;
        if (ImGui::MenuItem("Escape")) key = Keys::Escape;
        if (ImGui::MenuItem("Enter")) key = Keys::Enter;
        if (ImGui::MenuItem("Tab")) key = Keys::Tab;
        if (ImGui::MenuItem("Backspace")) key = Keys::Backspace;
        if (ImGui::MenuItem("Insert")) key = Keys::Insert;
        if (ImGui::MenuItem("Delete")) key = Keys::Delete;

        ImGui::Separator();

        if (ImGui::MenuItem("Right Arrow")) key = Keys::RightArrow;
        if (ImGui::MenuItem("Left Arrow")) key = Keys::LeftArrow;
        if (ImGui::MenuItem("Down Arrow")) key = Keys::DownArrow;
        if (ImGui::MenuItem("Up Arrow")) key = Keys::UpArrow;

        ImGui::Separator();

        if (ImGui::MenuItem("Page Up")) key = Keys::PageUp;
        if (ImGui::MenuItem("Page Down")) key = Keys::PageDown;
        if (ImGui::MenuItem("Home")) key = Keys::Home;
        if (ImGui::MenuItem("End")) key = Keys::End;
        if (ImGui::MenuItem("Caps Lock")) key = Keys::CapsLock;
        if (ImGui::MenuItem("Scroll Lock")) key = Keys::ScrollLock;
        if (ImGui::MenuItem("Num Lock")) key = Keys::NumLock;
        if (ImGui::MenuItem("Print Screen")) key = Keys::PrintScreen;
        if (ImGui::MenuItem("Pause")) key = Keys::Pause;

        ImGui::Separator();

        if (ImGui::MenuItem("F1")) key = Keys::F1;
        if (ImGui::MenuItem("F2")) key = Keys::F2;
        if (ImGui::MenuItem("F3")) key = Keys::F3;
        if (ImGui::MenuItem("F4")) key = Keys::F4;
        if (ImGui::MenuItem("F5")) key = Keys::F5;
        if (ImGui::MenuItem("F6")) key = Keys::F6;
        if (ImGui::MenuItem("F7")) key = Keys::F7;
        if (ImGui::MenuItem("F8")) key = Keys::F8;
        if (ImGui::MenuItem("F9")) key = Keys::F9;
        if (ImGui::MenuItem("F10")) key = Keys::F10;
        if (ImGui::MenuItem("F11")) key = Keys::F11;
        if (ImGui::MenuItem("F12")) key = Keys::F12;
        if (ImGui::MenuItem("F13")) key = Keys::F13;
        if (ImGui::MenuItem("F14")) key = Keys::F14;
        if (ImGui::MenuItem("F15")) key = Keys::F15;
        if (ImGui::MenuItem("F16")) key = Keys::F16;
        if (ImGui::MenuItem("F17")) key = Keys::F17;
        if (ImGui::MenuItem("F18")) key = Keys::F18;
        if (ImGui::MenuItem("F19")) key = Keys::F19;
        if (ImGui::MenuItem("F20")) key = Keys::F20;
        if (ImGui::MenuItem("F21")) key = Keys::F21;
        if (ImGui::MenuItem("F22")) key = Keys::F22;
        if (ImGui::MenuItem("F23")) key = Keys::F23;
        if (ImGui::MenuItem("F24")) key = Keys::F24;
        if (ImGui::MenuItem("F25")) key = Keys::F25;

        ImGui::Separator();

        if (ImGui::MenuItem("Num Pad Zero")) key = Keys::NumPadZero;
        if (ImGui::MenuItem("Num Pad One")) key = Keys::NumPadOne;
        if (ImGui::MenuItem("Num Pad Two")) key = Keys::NumPadTwo;
        if (ImGui::MenuItem("Num Pad Three")) key = Keys::NumPadThree;
        if (ImGui::MenuItem("Num Pad Four")) key = Keys::NumPadFour;
        if (ImGui::MenuItem("Num Pad Five")) key = Keys::NumPadFive;
        if (ImGui::MenuItem("Num Pad Six")) key = Keys::NumPadSix;
        if (ImGui::MenuItem("Num Pad Seven")) key = Keys::NumPadSeven;
        if (ImGui::MenuItem("Num Pad Eight")) key = Keys::NumPadEight;
        if (ImGui::MenuItem("Num Pad Nine")) key = Keys::NumPadNine;
        if (ImGui::MenuItem("Num Pad Decimal")) key = Keys::NumPadDecimal;
        if (ImGui::MenuItem("Num Pad Divide")) key = Keys::NumPadDivide;
        if (ImGui::MenuItem("Num Pad Multiply")) key = Keys::NumPadMultiply;
        if (ImGui::MenuItem("Num Pad Subtract")) key = Keys::NumPadSubtract;
        if (ImGui::MenuItem("Num Pad Add")) key = Keys::NumPadAdd;
        if (ImGui::MenuItem("Num Pad Enter")) key = Keys::NumPadEnter;
        if (ImGui::MenuItem("Num Pad Equal")) key = Keys::NumPadEqual;

        ImGui::Separator();

        if (ImGui::MenuItem("Mouse Button 1/Left")) key = Keys::MouseButtonLeft;
        if (ImGui::MenuItem("Mouse Button 2/Right")) key = Keys::MouseButtonRight;
        if (ImGui::MenuItem("Mouse Button 3/Middle")) key = Keys::MouseButtonMiddle;
        if (ImGui::MenuItem("Mouse Button 4")) key = Keys::MouseButton4;
        if (ImGui::MenuItem("Mouse Button 5")) key = Keys::MouseButton5;
        if (ImGui::MenuItem("Mouse Button 6")) key = Keys::MouseButton6;
        if (ImGui::MenuItem("Mouse Button 7")) key = Keys::MouseButton7;
        if (ImGui::MenuItem("Mouse Button 8/Last")) key = Keys::MouseButtonLast;

        ImGui::EndCombo();
    }
}