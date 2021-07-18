// Filesystem.cpp
// Last update 17/7/2021 by Madman10K
#include "Filesystem.hpp"

#ifndef PRODUCTION
#ifndef __MINGW32__
void Filesystem::display(std_filesystem::path& pt, UVK::Texture* textures, std::string& cpLoc, bool& bShow)
{
    ImGui::Begin("Filesystem##Widget", &bShow);

    static float padding = 20.0f;
    static float imageSize = 50.0f;
    float cellSize = padding + imageSize;

    ImGui::BeginChild("Explorer");

    // ImGui::GetContentRegionAvailWidth() marked as deprecated for some reason
    auto testing = (int)(ImGui::GetContentRegionAvail().x / cellSize);
    if (testing < 1)
    {
        testing = 1;
    }

    ImGui::Columns(testing, nullptr, false);

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

        // path.filename().c_str() shows only the first letter of a filename on Windows for some reason
        ImGui::TextWrapped("%s", path.filename().string().c_str());
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
    ImGui::End();
}
#endif
#endif