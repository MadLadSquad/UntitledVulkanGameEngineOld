// Filesystem.cpp
// Last update 2/8/2021 by Madman10K
#include <GL/glew.h>
#include "Filesystem.hpp"
#include "Assets/Asset.hpp"

#ifndef PRODUCTION
#ifndef __MINGW32__
void Filesystem::display(std_filesystem::path& pt, UVK::Texture* textures, std::unordered_map<std::string, UVK::Texture>& previews, bool& bShow)
{
    constexpr const char* audioExtensions[] = { ".wav", ".flac", ".m4a", ".ogg", ".mp3" };
    constexpr const char* imageExtensions[] = { ".jpeg", ".jpg", ".tiff", ".gif", ".bmp", ".png", ".tga", ".psd", ".pic" };
    constexpr const char* videoExtensions[] = { ".mov", ".m4v", ".mp4", ".mpeg", ".mkv", ".mpg", ".wmv", ".webm" };
    constexpr const char* objExtensions[] = { ".obj", ".fbx", ".glb", ".gltf", ".mp3" };
    constexpr const char* codeExtensions[] = { ".yaml", ".uvklevel", ".yml" };

    ImGui::Begin("Filesystem##Widget", &bShow);

    static float padding = 20.0f;
    static float imageSize = 50.0f;
    float cellSize = padding + imageSize;


    /**
     * The 2 static bools below this comment are used for displaying preview images. Preview images are stored
     * in a map of locations and textures. When a user navigates a directory, bChangedDir is switched to true.
     * This in the context of the "../" button will lead to a jump instruction(goto) being executed that skips the
     * iteration of the current folder, while if the user navigated a folder in the filesystem it will just break the
     * loop. The point is that once at L184 the program will loop back to itself which would clear the previews and
     * activate bChangedLastFrame which will then load up a new preview for every image
     */
    static bool bChangedDir = false;
    static bool bChangedLastFrame = false;

    if (bChangedDir)
    {
        for (auto& a : previews)
        {
            a.second.destroy();
        }

        previews.clear();

        bChangedLastFrame = true;
    }

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
            bChangedDir = true;
            goto backsection;
        }
        ImGui::TextWrapped("../");
        ImGui::NextColumn();
    }

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
                bChangedDir = true;
                break;
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
                    break;
                }
            }

            if (txt == nullptr)
            {
                for (const auto& b : imageExtensions)
                {
                    if (path.filename().extension().string() == b)
                    {
                        if (bChangedLastFrame)
                        {
                            UVK::Texture tx;
                            previews.insert(std::make_pair(path.string(), tx));
                            auto& preview = previews[path.string()];
                            preview = UVK::Texture(path.string());
                            preview.loadImgui();
                        }
                        txt = &previews[path.string()];
                        //txt = &textures[FS_ICON_IMAGE];
                        break;
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
                        break;
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
                        break;
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
                        break;
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
backsection:
    if (bChangedDir && !bChangedLastFrame)
    {
        bChangedLastFrame = true;
    }

    if (bChangedLastFrame)
    {
        bChangedLastFrame = false;
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