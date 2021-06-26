// Theme.cpp
// Last update 26/6/2021 by Madman10K
#include <Core.hpp>
#include "Theme.hpp"
#include <yaml.h>
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

#ifndef PRODUCTION
namespace YAML
{
    template<>
    struct convert<ImVec4>
    {
        static Node encode(const ImVec4& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, ImVec4& rhs)
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
}

YAML::Emitter& operator<<(YAML::Emitter& out, const ImVec4& vect)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << vect.w << YAML::EndSeq;
    return out;
}

void UVK::EditorTheme::setTheme(UVK::String theme)
{
    YAML::Node out;
    bool bUseCustomTheme = true;

    try
    {
        out = YAML::LoadFile(theme);
    }
    catch (YAML::BadFile&)
    {
        bUseCustomTheme = false;

        logger.consoleLog("Invalid theme location or file", UVK_LOG_TYPE_ERROR);
    }

    if (bUseCustomTheme)
    {
        if (out["windowBg"] && out["header"] && out["headerHovered"] && out["headerActive"] && out["button"] && out["buttonHovered"] && out["buttonActive"] && out["frame"] && out["frameHovered"] && out["frameActive"] && out["tab"] && out["tabHovered"] && out["tabActive"] && out["tabUnfocused"] && out["tabUnfocusedActive"] && out["titleBg"] && out["titleBgCollapsed"] && out["titleBgActive"] && out["menubarBg"])
        {
            textCol = out["textCol"].as<ImVec4>();
            windowBg = out["windowBg"].as<ImVec4>();
            header = out["header"].as<ImVec4>();
            headerHovered = out["headerHovered"].as<ImVec4>();
            headerActive = out["headerActive"].as<ImVec4>();
            button = out["button"].as<ImVec4>();
            buttonHovered = out["buttonHovered"].as<ImVec4>();
            buttonActive = out["buttonActive"].as<ImVec4>();
            frame = out["frame"].as<ImVec4>();
            frameHovered = out["frameHovered"].as<ImVec4>();
            frameActive = out["frameActive"].as<ImVec4>();
            tab = out["tab"].as<ImVec4>();
            tabHovered = out["tabHovered"].as<ImVec4>();
            tabActive = out["tabActive"].as<ImVec4>();
            tabUnfocused = out["tabUnfocused"].as<ImVec4>();
            tabUnfocusedActive = out["tabUnfocusedActive"].as<ImVec4>();
            titleBg = out["titleBg"].as<ImVec4>();
            titleBgCollapsed = out["titleBgCollapsed"].as<ImVec4>();
            titleBgActive = out["titleBgActive"].as<ImVec4>();
            menubarBG = out["menubarBg"].as<ImVec4>();
            windowRounding = out["window-rounding"].as<float>();
            fontLoc = out["font"].as<std::string>();
            fontSize = out["font-size"].as<int>();
        }
    }
}

void UVK::EditorTheme::useTheme()
{
    auto& colours = ImGui::GetStyle().Colors;

    colours[ImGuiCol_Text] = textCol;
    colours[ImGuiCol_WindowBg] = windowBg;

    colours[ImGuiCol_Header] = header;
    colours[ImGuiCol_HeaderHovered] = headerActive;
    colours[ImGuiCol_HeaderActive] = headerHovered;

    colours[ImGuiCol_Button] = button;
    colours[ImGuiCol_ButtonHovered] = buttonHovered;
    colours[ImGuiCol_ButtonActive] = buttonActive;

    colours[ImGuiCol_FrameBg] = frame;
    colours[ImGuiCol_FrameBgHovered] = frameHovered;
    colours[ImGuiCol_FrameBgActive] = frameActive;

    colours[ImGuiCol_Tab] = tab;
    colours[ImGuiCol_TabHovered] = tabHovered;
    colours[ImGuiCol_TabActive] = tabActive;
    colours[ImGuiCol_TabUnfocused] = tabUnfocused;
    colours[ImGuiCol_TabUnfocusedActive] = tabUnfocusedActive;

    colours[ImGuiCol_TitleBg] = titleBg;
    colours[ImGuiCol_TitleBgActive] = titleBgActive;
    colours[ImGuiCol_TitleBgCollapsed] = titleBgCollapsed;

    colours[ImGuiCol_MenuBarBg] = menubarBG;
}
#endif