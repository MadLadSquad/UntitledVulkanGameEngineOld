// Filesystem.cpp
// Last update 15/6/2021 by Madman10K
#include "Filesystem.hpp"

#ifndef PRODUCTION
#ifndef __MINGW32__
void Filesystem::display(std_filesystem::path& pt, std::array<UVK::Texture, 8>& textures, std::string& cpLoc, bool& bShow)
{
    ImGui::Begin("Filesystem##Widget", &bShow);

    static float padding = 20.0f;
    static float imageSize = 50.0f;
    float cellSize = padding + imageSize;

    ImGui::BeginChild("Explorer");

    // ImGui::GetContentRegionAvailWidth() marked as deprecated for some reason
    ImGui::Columns((int)(ImGui::GetContentRegionAvail().x / cellSize), nullptr, false);

    auto p = pt.string();
    Utility::sanitiseFilepath(p, true);
    pt = std_filesystem::path(p);


    // I AM FUCKING MAD, YOU KNOW WHAT, I AM NOT MAD I AM PISSED
    // YOU ARE SAYING THAT THIS CHECK:
    // if (p != "../Content/" || p != "../Content")
    // DOESN'T GO TROUGH BUT THE FOLLOWING DOES!!!
    // IT'S THE SAME SHIT HOLY FUCK WHAT IS HAPPENING
    if (!(p == "../Content/" || p == "../Content"))
    {

        // WHY DO WE NEED TO DO THIS HACK!!!
        ImGui::ImageButton((void*)(intptr_t)textures[3].getImage(), ImVec2(imageSize, imageSize));
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            pt = pt.parent_path();
        }
        ImGui::TextWrapped("../");
        ImGui::NextColumn();
    }

    constexpr const char* audioExtensions[] = { ".wav", ".flac", ".m4a", ".ogg", ".mp3" };
    constexpr const char* imageExtensions[] = { ".jpeg", ".jpg", ".tiff", ".gif", ".bmp", ".png", ".tga", ".psd", ".pic" };
    constexpr const char* videoExtensions[] = { ".mov", ".m4v", ".mp4", ".mpeg", ".mkv", ".mpg", ".wmv", ".webm" };
    constexpr const char* objExtensions[] = { ".obj", ".fbx", ".glb", ".gltf", ".mp3" };
    constexpr const char* codeExtensions[] = { ".yaml", ".uvklevel", ".yml" };

    for (auto& a : std_filesystem::directory_iterator(pt))
    {
        auto& path = a.path();

        UVK::Texture* txt;
        if (a.is_directory())
        {
            txt = &textures[3];
            // WHY DO WE NEED TO DO THIS HACK!!!
            ImGui::ImageButton((void*)(intptr_t)txt->getImage(), ImVec2(imageSize, imageSize));
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                pt /= path.filename();

            txt = nullptr;
        }
        else
        {
            for (const auto& b : audioExtensions)
            {
                if (path.filename().extension().string() == b)
                {
                    txt = &textures[0];
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : imageExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        txt = &textures[1];
                    }
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : videoExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        txt = &textures[2];
                    }
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : objExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        txt = &textures[5];
                    }
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : codeExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        txt = &textures[7];
                    }
                }
            }

            if (txt == nullptr && path.filename().extension().string() == ".ttf")
            {
                txt = &textures[4];
            }

            if (txt == nullptr)
            {
                txt = &textures[6];
            }

            ImGui::ImageButton((void*)(intptr_t)txt->getImage(), ImVec2(imageSize, imageSize));
            txt = nullptr;
        }

        ImGui::TextWrapped("%s", path.relative_path().filename().c_str());
        ImGui::NextColumn();
    }
    ImGui::Columns(1);
    ImGui::EndChild();
    ImGui::BeginGroup();
    ImGui::Separator();
    ImGui::Columns(2, nullptr, false);

    ImGui::SliderFloat("Image size", &imageSize, 1.0f, 256.0f);
    ImGui::NextColumn();
    ImGui::SliderFloat("Padding", &padding, 20.0f, 256.0f);
    ImGui::Columns(1);
    ImGui::EndGroup();
    /*std::string fileType;
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
     */
    ImGui::End();
}
#endif
#endif