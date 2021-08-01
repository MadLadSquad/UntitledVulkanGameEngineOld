// Filesystem.cpp
// Last update 1/8/2021 by Madman10K
#include <GL/glew.h>
#include "Filesystem.hpp"
#include "Assets/Asset.hpp"

#ifndef PRODUCTION
#ifndef __MINGW32__
void Filesystem::display(std_filesystem::path& pt, UVK::Texture* textures, bool& bShow)
{
    ImGui::Begin("Filesystem##Widget", &bShow);

    static float padding = 20.0f;
    static float imageSize = 50.0f;
    float cellSize = padding + imageSize;

    ImGui::BeginChild("Explorer");

    // ImGui::GetContentRegionAvailWidth() marked as deprecated for some reason
    auto columns = (int)(ImGui::GetContentRegionAvail().x / cellSize);
    if (columns < 1)
    {
        columns = 1;
    }

    ImGui::Columns(columns, nullptr, false);

    auto p = pt.string();
    Utility::sanitiseFilepath(p, true);
    pt = std_filesystem::path(p);

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
            txt = &textures[FS_ICON_FOLDER];
            // WHY DO WE NEED TO DO THIS HACK!!!
            ImGui::ImageButton((void*)(intptr_t)txt->getImage(), ImVec2(imageSize, imageSize));
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                pt /= path.filename();
            }

            txt = nullptr;
        }
        else
        {
            for (const auto& b : audioExtensions)
            {
                if (path.filename().extension().string() == b)
                {
                    txt = &textures[FS_ICON_AUDIO];
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : imageExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        /*
                        if (bChanged && bChangedTheChanged)
                        {
                            auto temp = UVK::Texture();
                            std::pair<std::string, UVK::Texture> pr;
                            pr.first = path.string();
                            pr.second = temp;
                            texturePreviews.insert(pr);

                            texturePreviews[path.string()] = UVK::Texture(path.string());
                            texturePreviews[path.string()].loadImgui();
                            txt = &texturePreviews[path.string()];

                            std::cout << "load" << path.string() << std::endl;

                        }
                        else
                        {
                            //std::cout << "use" << path.string() << std::endl;
                            txt = &texturePreviews[path.string()];
                        }*/
                        //std::cout << txt << std::endl;
                        txt = &textures[FS_ICON_IMAGE];
                        //for (auto& it : UVK::global.assetManager.data()[UVK::UVK_ASSET_TYPE_TEXTURE])
                        //{
                        //    if (it.location == path.filename().string())
                        //    {
                        //        txt = (UVK::Texture*)&it.data;
                        //    }
                        //}
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
                    }
                }
            }

            if (txt == nullptr && path.filename().extension().string() == ".ttf")
            {
                txt = &textures[FS_ICON_CODE];
            }

            if (txt == nullptr)
            {
                txt = &textures[FS_ICON_UNKNOWN];
            }
            //ImGui::BeginPopup()
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