// ProjectSettings.cpp
// Last update 18/2/2022 by Madman10K
#include "ProjectSettings.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

void UVK::ProjectSettingsWidget::displayProjectSettings(bool& bReturn, std::string& name, std::string& ver, std::string& enginever, std::string& startupLevel, bool& bOpen)
{
    ImGui::TextWrapped("Project Name");
    ImGui::SameLine();
    if (ImGui::InputText("##Project Name", &name) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Project Version");
    ImGui::SameLine();
    if (ImGui::InputText("##Project Version", &ver) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Engine Version");
    ImGui::SameLine();
    if (ImGui::InputText("##Engine Version", &enginever) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Startup Level Name");
    ImGui::SameLine();
    if (ImGui::InputText("##Startup Level Name", &startupLevel) || ImGui::IsItemActive())
        bReturn = true;
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