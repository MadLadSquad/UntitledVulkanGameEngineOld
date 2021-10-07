// Filesystem.cpp
// Last update 12/8/2021 by Madman10K
#include <GL/glew.h>
#include "Filesystem.hpp"
#ifndef PRODUCTION
#include "Assets/Asset.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

#ifndef __MINGW32__
void Filesystem::display(std_filesystem::path& pt, UVK::Texture* textures, std::unordered_map<std::string, UVK::Texture>& previews, bool& bShow)
{
    constexpr const char* audioExtensions[] = { ".wav", ".flac", ".m4a", ".ogg", ".mp3" };
    constexpr const char* imageExtensions[] = { ".jpeg", ".jpg", ".tiff", ".gif", ".bmp", ".png", ".tga", ".psd", ".pic" };
    constexpr const char* videoExtensions[] = { ".mov", ".m4v", ".mp4", ".mpeg", ".mkv", ".mpg", ".wmv", ".webm" };
    constexpr const char* objExtensions[] = { ".obj", ".fbx", ".glb", ".gltf", ".mp3" };
    constexpr const char* codeExtensions[] = { ".yaml", ".uvklevel", ".yml" };

    static float padding = 20.0f;
    static float imageSize = 50.0f;
    float cellSize = padding + imageSize;
    static bool bUsePreviews = true;
    int columns;

    ImGui::Begin("Filesystem##Widget", &bShow, ImGuiWindowFlags_MenuBar);

    bool bCreateFile = false;
    bool bRemoveFile = false;
    bool bAddDirectory = false;

    static std::string selectedFile;

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::MenuItem("+ Add File"))
            bCreateFile = true;

        if (ImGui::MenuItem("- Remove File"))
            bRemoveFile = true;

        if (ImGui::MenuItem("+ Add Directory"))
            bAddDirectory = true;

        ImGui::EndMenuBar();
    }

    ImGui::BeginChild("Explorer");

    columns = (int)(ImGui::GetContentRegionAvail().x / cellSize);
    if (columns < 1)
    {
        columns = 1;
    }

    ImGui::Columns(columns, nullptr, false);

    auto p = pt.string();
    UVK::Utility::sanitiseFilepath(p, true);
    pt = std_filesystem::path(p);

    ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f });
    if (!(p == "../Content/" || p == "../Content"))
    {
        // WHY DO WE NEED TO DO THIS HACK!!!
        ImGui::ImageButton((void*)(intptr_t)textures[FS_ICON_FOLDER].getImage(), ImVec2(imageSize, imageSize));
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            pt = pt.parent_path();
        }
        ImGui::TextWrapped("../");
        ImGui::NextColumn();
    }

    for (auto& a : std_filesystem::directory_iterator(pt))
    {
        auto& path = a.path();

        UVK::Texture* txt = nullptr;

        if (bAddDirectory)
        {
            if (std_filesystem::exists(pt/"NewFolder"))
            {
                int i = 0;
                while (std_filesystem::exists(pt.string() + "/NewFolder" + std::to_string(i)))
                    i++;

                create_directory(std_filesystem::path(pt.string() + "/NewFolder" + std::to_string(i)));
            }
            else
                create_directory(pt/"NewFolder");

            bAddDirectory = false;
        }

        if (bCreateFile)
        {
            std::cout << pt.string() << std::endl;
            if (std_filesystem::exists(pt.string() + "/NewFile.txt"))
            {
                int i = 0;
                while (std_filesystem::exists(pt.string() + "/NewFile" + std::to_string(i) + ".txt"))
                    i++;

                std::ofstream out(pt.string() + "/NewFile" + std::to_string(i) + ".txt");
                out << std::endl;
                out.close();
            }
            else
            {
                std::ofstream out(pt.string() + "/NewFile.txt");
                out << std::endl;
                out.close();
            }

            bCreateFile = false;
        }

        if (bRemoveFile)
        {
            if (is_directory(std_filesystem::path(selectedFile)))
                remove_all(std_filesystem::path(selectedFile));
            else
                remove(std_filesystem::path(selectedFile));

            selectedFile.clear();
            bRemoveFile = false;
        }

        if (a.is_directory())
        {
            txt = &textures[FS_ICON_FOLDER];
            // WHY DO WE NEED TO DO THIS HACK!!!
            ImGui::ImageButton((void*)(intptr_t)txt->getImage(), ImVec2(imageSize, imageSize));

            if (ImGui::IsItemHovered())
            {
                if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    pt /= path.filename();
                    std::cout << pt.string() << std::endl;
                    selectedFile.clear();
                    break;
                }

                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                    selectedFile = path.string();
                }
            }
        }
        else
        {
            for (const auto& b : audioExtensions)
            {
                if (path.filename().extension().string() == b)
                {
                    txt = &textures[FS_ICON_AUDIO];
                    goto render_image;
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : imageExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        /*if (bUsePreviews)
                        {
                            if (bChangedLastFrame)
                            {
                                UVK::Texture tx;
                                previews.insert(std::make_pair(path.filename().string(), tx));
                                auto& preview = previews[path.filename().string()];
                                preview = UVK::Texture(path.string());
                                preview.loadImgui();
                            }
                            txt = &previews[path.filename().string()];

                        }
                        else
                        {

                        }*/
                        txt = &textures[FS_ICON_IMAGE];
                        goto render_image;
                    }
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : videoExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        txt = &textures[FS_ICON_VIDEO];
                        goto render_image;
                    }
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : objExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        txt = &textures[FS_ICON_MODEL];
                        goto render_image;
                    }
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : codeExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        txt = &textures[FS_ICON_CODE];
                        goto render_image;
                    }
                }
            }

            if (txt == nullptr && path.filename().extension().string() == ".ttf")
            {
                txt = &textures[FS_ICON_CODE];
                goto render_image;
            }

            if (txt == nullptr)
            {
                txt = &textures[FS_ICON_UNKNOWN];
            }

render_image:
            ImGui::ImageButton((void*)(intptr_t)txt->getImage(), ImVec2(imageSize, imageSize));
            if (ImGui::IsItemHovered())
            {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                    selectedFile = path.string();
                }
            }

            txt = nullptr;
        }

        // path.filename().c_str() shows only the first letter of a filename on Windows for some reason
        ImGui::TextWrapped("%s", path.filename().string().c_str());
        ImGui::NextColumn();
    }
    ImGui::PopStyleColor();
    ImGui::Columns(1);

    ImGui::EndChild();
    ImGui::BeginGroup();
    ImGui::Separator();
    ImGui::Columns(3, nullptr, false);

    ImGui::TextWrapped("Image size");
    ImGui::SameLine();
    ImGui::SliderFloat("##Image size", &imageSize, 1.0f, 256.0f);
    ImGui::NextColumn();

    ImGui::TextWrapped("Padding");
    ImGui::SameLine();
    ImGui::SliderFloat("##Padding", &padding, 20.0f, 256.0f);
    ImGui::NextColumn();

    ImGui::TextWrapped("Display preview images");
    ImGui::SameLine();
    ImGui::Checkbox("##Display preview images", &bUsePreviews);
    ImGui::NextColumn();

    ImGui::Columns(1);
    ImGui::EndGroup();
    ImGui::End();
}
#endif
#endif