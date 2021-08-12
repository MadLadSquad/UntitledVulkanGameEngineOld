// Theme.cpp
// Last update 12/8/2021 by Madman10K
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
        out = YAML::LoadFile("../Config/Settings/" + std::string(theme) + ".uvktheme");
    }
    catch (YAML::BadFile&)
    {
        logger.consoleLog("Invalid theme location or file", UVK_LOG_TYPE_ERROR);
        return;
    }

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
        popupBG = out["popupBg"].as<ImVec4>();
        windowRounding = out["window-rounding"].as<float>();
        fontLoc = "../Content/" + out["font"].as<std::string>();
        fontSize = out["font-size"].as<int>();
    }

}

void UVK::EditorTheme::useTheme()
{
    auto& colours = ImGui::GetStyle().Colors;

    colours[ImGuiCol_Text] = textCol;
    colours[ImGuiCol_WindowBg] = windowBg;

    colours[ImGuiCol_Header] = header;
    colours[ImGuiCol_HeaderHovered] = headerHovered;
    colours[ImGuiCol_HeaderActive] = headerActive;

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
    colours[ImGuiCol_PopupBg] = popupBG;
}

void UVK::EditorTheme::save(UVK::String filename, UVK::String font, int fontSz)
{
    const auto& colours = ImGui::GetStyle().Colors;
    const auto& io = ImGui::GetIO();

    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "textCol" << YAML::Value << colours[ImGuiCol_Text];
    out << YAML::Key << "windowBg" << YAML::Value << colours[ImGuiCol_WindowBg];

    out << YAML::Key << "header" << YAML::Value << colours[ImGuiCol_Header];
    out << YAML::Key << "headerActive" << YAML::Value << colours[ImGuiCol_HeaderActive];
    out << YAML::Key << "headerHovered" << YAML::Value << colours[ImGuiCol_HeaderHovered];

    out << YAML::Key << "button" << YAML::Value << colours[ImGuiCol_Button];
    out << YAML::Key << "buttonHovered" << YAML::Value << colours[ImGuiCol_ButtonHovered];
    out << YAML::Key << "buttonActive" << YAML::Value << colours[ImGuiCol_ButtonActive];

    out << YAML::Key << "frame" << YAML::Value << colours[ImGuiCol_FrameBg];
    out << YAML::Key << "frameHovered" << YAML::Value << colours[ImGuiCol_FrameBgHovered];
    out << YAML::Key << "frameActive" << YAML::Value << colours[ImGuiCol_FrameBgActive];

    out << YAML::Key << "tab" << YAML::Value << colours[ImGuiCol_Tab];
    out << YAML::Key << "tabHovered" << YAML::Value << colours[ImGuiCol_TabHovered];
    out << YAML::Key << "tabActive" << YAML::Value << colours[ImGuiCol_TabActive];
    out << YAML::Key << "tabUnfocused" << YAML::Value << colours[ImGuiCol_TabUnfocused];
    out << YAML::Key << "tabUnfocusedActive" << YAML::Value << colours[ImGuiCol_TabUnfocusedActive];

    out << YAML::Key << "titleBg" << YAML::Value << colours[ImGuiCol_TitleBg];
    out << YAML::Key << "titleBgActive" << YAML::Value << colours[ImGuiCol_TitleBgActive];
    out << YAML::Key << "titleBgCollapsed" << YAML::Value << colours[ImGuiCol_TitleBgCollapsed];

    out << YAML::Key << "menubarBg" << YAML::Value << colours[ImGuiCol_MenuBarBg];
    out << YAML::Key << "popupBg" << YAML::Value << colours[ImGuiCol_PopupBg];

    out << YAML::Key << "font" << YAML::Value << font;
    out << YAML::Key << "font-size" << YAML::Value << fontSz;

    out << YAML::Key << "window-rounding" << YAML::Value << ImGui::GetStyle().WindowRounding;
    out << YAML::EndMap;

    std::ofstream file(filename);
    file << out.c_str();
    file.close();
}

#endif