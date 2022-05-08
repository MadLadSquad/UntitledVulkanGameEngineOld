#include "ProjectSettings.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <UVKBuildTool/src/CMakeGenerator.hpp>
#include <UVKBuildTool/src/ActorListGenerator.hpp>
#include <UVKBuildTool/src/SourceGenerator.hpp>

void UVK::ProjectSettingsWidget::displayProjectSettings(bool& bReturn, UVK::FString& name, UVK::FString& ver, UVK::FString& enginever, UVK::FString& startupLevel, bool& bOpen) noexcept
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

    ImGui::TextWrapped("Build settings");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("These settings need to be edited manually in the uvproj.yaml file!");
        ImGui::EndTooltip();
    }
    //ImGui::TextUnformatted("%s", node["additional-include-directories"]);
    ImGui::Separator();

    if (ImGui::Button("Close"))
    {
        bOpen = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        // TODO: output this with the custom libraries and files so that the configuration doesn't get overridden
        YAML::Emitter o;
        o << YAML::BeginMap << YAML::Key << "name" << YAML::Value << name.c_str();
        o << YAML::Key << "startup-level" << YAML::Value << startupLevel.c_str();
        o << YAML::Key << "version" << YAML::Value << ver.c_str();
        o << YAML::Key << "engine-version" << YAML::Value << enginever.c_str();

        YAML::Node config;
        try
        {
            config = YAML::LoadFile((UVK::FString(UVK_CONFIG_PRJ_PATH) + "uvproj.yaml").c_str());
        }
        catch (YAML::BadFile&)
        {
            logger.consoleLog("Couldn't open the uvproj.yaml file!", UVK_LOG_TYPE_ERROR);
            std::terminate();
        }

        if (config["additional-include-directories"])
            o << YAML::Key << "additional-include-directories" << YAML::Value << config["additional-include-directories"];
        if (config["additional-subdirectories"])
            o << YAML::Key << "additional-subdirectories" << YAML::Value << config["additional-subdirectories"];
        if (config["additional-link-libraries"])
            o << YAML::Key << "additional-link-libraries" << YAML::Value << config["additional-link-libraries"];
        if (config["additional-source-libraries"])
            o << YAML::Key << "additional-source-libraries" << YAML::Value << config["additional-source-libraries"];
        if (config["additional-header-libraries"])
            o << YAML::Key << "additional-header-libraries" << YAML::Value << config["additional-header-libraries"];
        o << YAML::EndMap;

        std::ofstream out("../uvproj.yaml");
        out << o.c_str() << std::endl;// << std::endl << node["additional-include-directories"] << "\n" << node["additional-subdirectories"] << "\n" << node["additional-link-libraries"] << "\n" << node["additional-source-libraries"] << "\n" << node["additional-header-libraries"];
        out.close();

        // The following lines are sourced from the main.cpp file in the UVKBuildTool CLI
        bool bSetReadable;

        UVK::FString startupLevelName;

        std::ifstream i(UBT::getPath() + "Generated/ActorList.hpp");
        bSetReadable = i.is_open();

        if (config["startup-level"])
        {
            startupLevelName = config["startup-level"].as<std::string>();
        }

        UBT::CMakeInfoData data;

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


//        static int lnt;
//#ifndef _WIN32
//        lnt = system("cd ../UVKBuildTool/build && ./UVKBuildTool --generate && cd ../../");
//#else
//        lnt = system("cd ../UVKBuildTool/build && UVKBuildTool.exe --generate && cd ../../");
//#endif
//        if (lnt)
//        {
//
//        }
    }
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("If you click \"Save\" your project's generated files will be regenerated!");
        ImGui::EndTooltip();
    }
    ImGui::EndPopup();
}