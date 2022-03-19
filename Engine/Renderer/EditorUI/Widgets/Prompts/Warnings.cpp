// Warnings.cpp
// Last update 18/2/2022 by Madman10K
#include <GL/glew.h>
#include "Warnings.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <Core/Global.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <glfw3.h>
#include <UVKBuildTool/src/CMakeGenerator.hpp>
#include <UVKBuildTool/src/SourceGenerator.hpp>
#include <UVKBuildTool/src/ActorListGenerator.hpp>

void Warnings::displayExitWarning(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("WARNING##EXITWARNING"))
        ImGui::OpenPopup("WARNING##EXITWARNING");
    if (ImGui::BeginPopupModal("WARNING##EXITWARNING", &bOpen))
    {
        ImGui::TextWrapped("WARNING: You are exiting the editor! Any changes that were not saved will not be!");
        if (ImGui::Button("Return##ed"))
            bOpen = false;
        ImGui::SameLine();
        if (ImGui::Button("Exit##ed"))
        {
            bOpen = false;
            glfwSetWindowShouldClose(UVK::global.window.getWindow(), GL_TRUE);
        }

        ImGui::EndPopup();
    }
}

void Warnings::displayGenerateWarning(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("WARNING##GENERATEWARNING"))
        ImGui::OpenPopup("WARNING##GENERATEWARNING");
    if (ImGui::BeginPopupModal("WARNING##GENERATEWARNING", &bOpen))
    {
        ImGui::TextWrapped("Regenerate files?");
        if (ImGui::Button("Close##ed"))
            bOpen = false;
        ImGui::SameLine();
        if (ImGui::Button("Regenerate##ed"))
        {
            std::string startupLevelName;
            YAML::Node config;
            std::string name;
            UBT::CMakeInfoData data;

            try
            {
                config = YAML::LoadFile("../../uvproj.yaml");
            }
            catch (YAML::BadFile&)
            {
                std::cout << "Could not locate file" << std::endl;
            }

            std::ifstream i(UBT::getPath() + "Generated/ActorList.hpp");
            bool bSetReadable = i.is_open();

            if (config["startup-level"])
                startupLevelName = config["startup-level"].as<std::string>();
            if (config["name"])
                name = config["name"].as<std::string>();

            UBT::addIncludeDirectories(config, data);
            UBT::addSubdirectories(config, data);
            UBT::addLinkLibraries(config, data);
            UBT::addHeaderLibraries(config, data);
            UBT::addSourceLibraries(config, data);

            if (!bSetReadable) UBT::generateSet();
            UBT::generateCmake(name.c_str(), data);
            UBT::generateGame(name.c_str());
            UBT::generateMain(startupLevelName.c_str(), name.c_str());
            UBT::generateDef();
            bOpen = false;
        }

        ImGui::EndPopup();
    }
}

void Warnings::displaySaveWarning(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("WARNING##SAVEWARNING"))
        ImGui::OpenPopup("WARNING##SAVEWARNING");
    if (ImGui::BeginPopupModal("WARNING##SAVEWARNING", &bOpen))
    {
        ImGui::TextWrapped("Save Level?");
        if (ImGui::Button("Close##ed"))
            bOpen = false;
        ImGui::SameLine();
        if (ImGui::Button("Save##ed"))
            UVK::Level::save(UVK::global.levelLocation.c_str());

        ImGui::EndPopup();
    }
}
#endif