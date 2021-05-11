// Filesystem.cpp
// Last update 5/04/2021 by Madman10K
#include "Filesystem.hpp"

#ifndef __MINGW32__
void Filesystem::display(std_filesystem::path& pt, std::string& cpLoc)
{
    ImGui::Begin("Filesystem##Widget", nullptr);
    std::string fileType;
    auto temp = absolute(pt).string();
    Utility::sanitiseFilepath(temp, true);

    if (ImGui::Selectable("[DIR] ../"))
    {
        if (temp[temp.size() - 2] == '/')
            temp.erase(temp.size() - 2);
        else if (temp[temp.size() - 1] == '/' && temp.size() != 1)
            temp.erase(temp.size() - 1);

        if (temp.size() != 1)
        {
            auto last = temp.find_last_of('/');

            temp.erase(last);
            temp += "/";
        }

        pt = std_filesystem::path(temp);
    }

    for (auto& p: std_filesystem::directory_iterator(pt))
    {
        if (p.is_directory())
        {
            fileType = "[DIR] ";
        }
        else if (p.path().filename().extension().string() == ".wav" || p.path().filename().extension().string() == ".mp3" || p.path().filename().extension().string() == ".flac")
        {
            fileType = "[SND] ";
        }
        else if (p.path().filename().extension().string() == ".obj" || p.path().filename().extension().string() == ".mtl" || p.path().filename().extension().string() == ".fbx")
        {
            fileType = "[3D] ";
        }
        else if (p.path().filename().extension().string() == ".png" || p.path().filename().extension().string() == ".jpg" || p.path().filename().extension().string() == ".jpeg")
        {
            fileType = "[IMG] ";
        }
        else if (p.path().filename().extension().string() == ".mp4" || p.path().filename().extension().string() == ".mov")
        {
            fileType = "[VID] ";
        }
        else if (p.path().filename().extension().string() == ".vert" || p.path().filename().extension().string() == ".frag" || p.path().filename().extension().string() == ".gl" || p.path().filename().extension().string() == ".glsl" || p.path().filename().extension().string() == ".spv" || p.path().filename().extension().string() == ".vk")
        {
            fileType = "[SHADER] ";
        }
        else if (p.path().filename().extension().string() == ".sh" || p.path().filename().extension().string() == ".cmd" || p.path().filename().extension().string() == ".bat" || p.path().filename().extension().string() == ".py" || p.path().filename().extension().string() == ".perl")
        {
            fileType = "[SCRIPT] ";
        }
        else if (p.path().filename().string() == ".yaml" || p.path().filename().string() == ".yml" || p.path().filename().string() == ".uvklevel")
        {
            fileType = "[LEVEL/CONFIG] ";
        }
        else
        {
            fileType = "[?] ";
        }

        if (ImGui::Selectable(static_cast<std::string>(fileType + p.path().filename().string()).c_str(), false, ImGuiSelectableFlags_AllowDoubleClick))
        {
            if (ImGui::IsMouseDoubleClicked(0) && fileType == "[DIR] ")
            {
                pt = std_filesystem::path(p.path().string());
            }
            else
            {
                cpLoc = p.path().string();
            }
        }
    }
    ImGui::End();
}
#endif