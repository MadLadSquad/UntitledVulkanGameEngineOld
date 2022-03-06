// RemoveFile.cpp
// Last update 18/2/2022 by Madman10K
#include "RemoveFile.hpp"
#ifndef PRODUCTION
#include <Core.hpp>
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <UVKBuildTool/src/ActorListGenerator.hpp>

bool RemoveFile::display(bool& bShow)
{
    bool bReturn = false;
    if (!ImGui::IsPopupOpen("Remove File"))
        ImGui::OpenPopup("Remove File");

    if (ImGui::BeginPopupModal("Remove File", &bShow))
    {
        static std::string in;
        static bool bSO = false;

        ImGui::TextWrapped("Scriptable Object?");
        ImGui::SameLine();
        ImGui::Checkbox("##Scriptable Object?", &bSO);

        ImGui::TextWrapped("File Location: Source/");
        ImGui::SameLine();
        if (ImGui::InputText("##File to delete", &in) || ImGui::IsItemActive())
            bReturn = true;

        if (ImGui::Button("Close##delete"))
        {
            bShow = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Delete##delete"))
        {

            if (bSO)
            {

#ifndef __MINGW32__
                UBT::removeClass(in);
                try
                {
                    std_filesystem::remove("../Source/" + in + ".hpp");
                    std_filesystem::remove("../Source/" + in + ".cpp");
                }
                catch (std_filesystem::filesystem_error&)
                {
                    logger.consoleLog("Failed to delete files", UVK_LOG_TYPE_ERROR);
                }
#endif
            }
            else
            {
#ifndef __MINGW32__
                try
                {
                    std_filesystem::remove("../Source/" + in + ".hpp");
                    std_filesystem::remove("../Source/" + in + ".cpp");
                }
                catch (std_filesystem::filesystem_error&)
                {
                    logger.consoleLog("Failed to delete files", UVK_LOG_TYPE_ERROR);
                }
#endif
            }

        }
        ImGui::EndPopup();
    }
    return bReturn;
}
#endif