// RemoveFile.cpp
// Last update 9/6/2021 by Madman10K
#include "RemoveFile.hpp"
#include <Core.hpp>
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

void RemoveFile::display(bool& bShow)
{
    static int lnt = 0;
    ImGui::Begin("RemoveFile", &bShow);

    static std::string in;
    static bool bSO = false;
    static bool error = false;

    ImGui::Checkbox("Scriptable Object?", &bSO);
    ImGui::InputTextWithHint("File to delete", "Location starts from the source folder, do not specify the file's extension, only the name", &in);

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
            try
            {
#ifndef _WIN32
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build/ && ./UVKBuildTool --actor " + in + " --remove").c_str());
#else
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build/ && UVKBuildTool.exe --actor " + in + " --remove").c_str());
#endif
                std_filesystem::remove("../../Source/" + in + ".hpp");
                std_filesystem::remove("../../Source/" + in + ".cpp");
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
                std_filesystem::remove("../../Source/" + in + ".hpp");
                std_filesystem::remove("../../Source/" + in + ".cpp");
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
    }

    if (lnt)
    {

    }
    ImGui::End();
}