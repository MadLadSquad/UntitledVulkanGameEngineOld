// RemoveFile.cpp
// Last update 1/8/2021 by Madman10K
#include "RemoveFile.hpp"
#include <Core.hpp>
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

#ifndef PRODUCTION
void RemoveFile::display(bool& bShow)
{
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
        ImGui::InputText("##File to delete", &in);

        if (ImGui::Button("Close##delete"))
        {
            bShow = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Delete##delete"))
        {
            int8_t lnt = 0;
            bool error = false;
            std::string gen;
            if (bSO)
            {

#ifndef __MINGW32__

                try
                {
#ifndef _WIN32
                    gen = "cd ../UVKBuildTool/build/ && ./UVKBuildTool --actor " + in + " --remove";
#else
                    gen = "cd ../UVKBuildTool/build/ && UVKBuildTool.exe --actor " + in + " --remove";
#endif
                    std_filesystem::remove("../Source/" + in + ".hpp");
                    std_filesystem::remove("../Source/" + in + ".cpp");
                }
                catch (std_filesystem::filesystem_error&)
                {
                    logger.consoleLog("Failed to delete files", UVK_LOG_TYPE_ERROR);
                    error = true;
                }

                if (!error)
                {
                    bShow = false;
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
                    error = true;
                }

                if (!error)
                {
                    bShow = false;
                }
#endif
            }
            if (system(gen.c_str()))
            {

            }
        }
        ImGui::EndPopup();
    }
}
#endif