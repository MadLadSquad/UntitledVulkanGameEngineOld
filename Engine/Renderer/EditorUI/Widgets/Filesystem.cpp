// Filesystem.cpp
// Last update 13/10/2021 by Madman10K
#include <GL/glew.h>
#include "Filesystem.hpp"
#ifndef PRODUCTION
#include "Assets/Asset.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <State/StateTracker.hpp>

#ifndef __MINGW32__
bool Filesystem::display(std_filesystem::path& pt, UVK::Texture* textures, bool& bShow)
{
    // Variables for the UI
    static float padding = 20.0f;
    static float imageSize = 50.0f;
    float cellSize = padding + imageSize;
    int columns;

    // Variables for previews and folder refresh
    static bool bUsePreviews = false;
    volatile static bool bCurrentlyUsingPreviews = false;
    volatile static bool bNewFolder = true;
    static unsigned int fileNum = 0;
    static int maxFileNum = 64;
    static std::vector<UVK::Texture> previews;

    if (bNewFolder)
    {
        bCurrentlyUsingPreviews = false;
        fileNum = 0;
        for (auto& a : std_filesystem::directory_iterator(pt))
            fileNum++;

        for (auto& a : previews)
            a.destroy();
        previews.clear();
    }

    if (bUsePreviews)
        bCurrentlyUsingPreviews = fileNum >= maxFileNum ? false : true;

    if (bCurrentlyUsingPreviews && (previews.size() != maxFileNum || bNewFolder))
        previews.resize(maxFileNum);

    // The current file represented as a string
    static std_filesystem::path selectedFile;

    ImGui::Begin("Filesystem##Widget", &bShow, ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::MenuItem("+ Add File"))
        {
            createFile(pt);
            bNewFolder = true;
            return false;
        }

        if (ImGui::MenuItem("- Remove File"))
        {
            deleteFile(pt, selectedFile);
            bNewFolder = true;
            return false;
        }

        if (ImGui::MenuItem("+ Add Directory"))
        {
            createFolder(pt);
            bNewFolder = true;
            return false;
        }

        ImGui::EndMenuBar();
    }

    ImGui::BeginChild("Explorer");

    columns = (int)(ImGui::GetContentRegionAvail().x / cellSize);
    columns = columns < 1 ? 1 : columns;

    ImGui::Columns(columns, nullptr, false);

    auto p = pt.string();
    UVK::Utility::sanitiseFilepath(p, true);
    pt = std_filesystem::path(p);

    ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f });
    if (!(p == "../Content/" || p == "../Content"))
    {
        ImGui::ImageButton((void*)(intptr_t)textures[FS_ICON_FOLDER].getImage(), ImVec2(imageSize, imageSize));
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            pt = pt.parent_path();
            bNewFolder = true;
            return false;
        }

        ImGui::TextWrapped("../");
        ImGui::NextColumn();
    }

    int i = 0;
    for (auto& a : std_filesystem::directory_iterator(pt))
    {
        i++;
        auto& path = a.path();
        if (a.is_directory())
        {
            ImGui::ImageButton((void*)(intptr_t)textures[FS_ICON_FOLDER].getImage(), ImVec2(imageSize, imageSize));
            if (ImGui::IsItemHovered())
            {
                if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    pt = pt / path.filename();
                    selectedFile.clear();
                    bNewFolder = true;
                    return false;
                }

                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                    selectedFile = path;
            }
        }
        else
        {
            ImGui::ImageButton((void*)(intptr_t)(selectTextures(textures, a, previews, bCurrentlyUsingPreviews, i, bNewFolder)->getImage()), ImVec2(imageSize, imageSize));
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                selectedFile = path;
        }

        // path.filename().c_str() shows only the first letter of a filename on Windows for some reason
        ImGui::TextWrapped("%s", path.filename().string().c_str());
        ImGui::NextColumn();
    }
    bNewFolder = false;
    ImGui::PopStyleColor();
    ImGui::Columns(1);

    ImGui::EndChild();
    ImGui::BeginGroup();
    ImGui::Separator();
    ImGui::Columns(4, nullptr, false);

    ImGui::TextWrapped("Image size");
    ImGui::SameLine();
    ImGui::SliderFloat("##Image size", &imageSize, 1.0f, 256.0f);
    ImGui::NextColumn();

    ImGui::TextWrapped("Padding");
    ImGui::SameLine();
    ImGui::SliderFloat("##Padding", &padding, 20.0f, 256.0f);
    ImGui::NextColumn();

    ImGui::TextWrapped("Max Previews");
    if (ImGui::IsItemHovered())
    {
        ImGui::SetNextWindowSize(ImVec2(300.0f, 55.0f));
        ImGui::BeginTooltip();
        ImGui::TextWrapped("If there are more files in the directory than the integer, then previews are not loaded!");
        ImGui::EndTooltip();
    }
    ImGui::SameLine();
    ImGui::SliderInt("##MaxImages", &maxFileNum, 0, 1024);
    ImGui::NextColumn();

    ImGui::SetColumnWidth(3, 150.0f);
    ImGui::TextWrapped("Previews?");
    ImGui::SameLine();
    ImGui::Checkbox("##Display preview images", &bUsePreviews);

    ImGui::Columns(1);
    ImGui::EndGroup();
    ImGui::End();
    return false;
}

void Filesystem::createFile(const std_filesystem::path &pt)
{
    if (std_filesystem::exists(pt/"NewFile.txt"))
    {
        int i = 0;
        while (std_filesystem::exists(pt/("NewFile" + std::to_string(i) + ".txt")))
            i++;

        std::ofstream out(pt/("NewFile" + std::to_string(i) + ".txt"));
        out << std::endl;
        out.close();

        UVK::Transaction transaction =
        {
            .undofunc = [](UVK::TransactionPayload& payload)
            {
                if (std_filesystem::exists(payload.coreComponent.name))
                    remove(std_filesystem::path(payload.coreComponent.name));
            },
            .redofunc = [](UVK::TransactionPayload& payload)
            {
                std::ofstream out(payload.coreComponent.name);
                out << std::endl;
                out.close();
            },
            .transactionPayload =
            {
                .coreComponent =
                {
                    .name = (pt/("NewFile" + std::to_string(i) + ".txt")).string()
                }
            }
        };
        UVK::StateTracker::push(transaction);
    }
    else
    {
        std::ofstream out(pt/"NewFile.txt");
        out << std::endl;
        out.close();

        UVK::Transaction transaction =
        {
            .undofunc = [](UVK::TransactionPayload& payload)
            {
                if (std_filesystem::exists(payload.coreComponent.name))
                    remove(std_filesystem::path(payload.coreComponent.name));
            },
            .redofunc = [](UVK::TransactionPayload& payload)
            {
                std::ofstream out(payload.coreComponent.name);
                out << std::endl;
                out.close();
            },
            .transactionPayload
            {
                .coreComponent =
                {
                    .name = (pt/"NewFile.txt").string()
                }
            }

        };
        UVK::StateTracker::push(transaction);
    }
}

void Filesystem::createFolder(const std_filesystem::path& pt)
{
    if (std_filesystem::exists(pt/"NewFolder"))
    {
        int i = 0;
        while (std_filesystem::exists(pt/("NewFolder" + std::to_string(i))))
            i++;

        create_directory(std_filesystem::path(pt/("NewFolder" + std::to_string(i))));

        UVK::Transaction transaction =
        {
            .undofunc = [](UVK::TransactionPayload& payload)
            {
                remove_all(std_filesystem::path(payload.coreComponent.name));
            },
            .redofunc = [](UVK::TransactionPayload& payload)
            {
                if (!std_filesystem::exists(payload.coreComponent.name))
                    std_filesystem::create_directory(std_filesystem::path(payload.coreComponent.name));
            },
            .transactionPayload
            {
                .coreComponent =
                {
                    .name = (pt/("NewFolder" + std::to_string(i))).string()
                }
            }
        };
        UVK::StateTracker::push(transaction);
    }
    else
    {
        create_directory(pt/"NewFolder");

        UVK::Transaction transaction =
        {
            .undofunc = [](UVK::TransactionPayload& payload)
            {
                remove_all(std_filesystem::path(payload.coreComponent.name));
            },
            .redofunc = [](UVK::TransactionPayload& payload)
            {
                if (!std_filesystem::exists(payload.coreComponent.name))
                    std_filesystem::create_directory(std_filesystem::path(payload.coreComponent.name));
            },
            .transactionPayload =
            {
                .coreComponent =
                {
                    .name = (pt/"NewFolder").string()
                }
            }
        };
        UVK::StateTracker::push(transaction);
    }
}

void Filesystem::deleteFile(std_filesystem::path& pt, std_filesystem::path& selectedFile)
{
    if (is_directory(selectedFile))
    {
        // TODO: Add a warning here
        //create_directory(std_filesystem::path("../Generated/EditorFS")/selectedFile.filename());
        //copy(selectedFile, std_filesystem::path("../Generated/EditorFS")/selectedFile.filename(), std_filesystem::copy_options::recursive);
        remove_all(selectedFile);
        UVK::Transaction transaction =
        {
            .undofunc = [](UVK::TransactionPayload& payload)
            {
                //if (!act.valid())
                // TODO: Recreate the whole directory structure
                std_filesystem::create_directory(std_filesystem::path(payload.coreComponent.name));
            },
            .redofunc = [](UVK::TransactionPayload& payload)
            {
                std_filesystem::remove_all(std_filesystem::path(payload.coreComponent.name));
            },
            .transactionPayload =
            {
                .coreComponent =
                {
                    .name = selectedFile.string(),
                    .id = 330,
                    .devName = "EngineFilesystemFolderDelete"
                },
                .deltaCoreComponent
                {

                }
            }
        };
        UVK::StateTracker::push(transaction);
    }
    else
    {
        std::ifstream in(selectedFile);
        std::string buf;
        std::string temp;

        while (std::getline(in, temp))
            buf.append(temp + '\n');

        remove(selectedFile);

        UVK::Transaction transaction =
        {
            .undofunc = [](UVK::TransactionPayload& payload)
            {
                std::ofstream out(std_filesystem::path(payload.coreComponent.name));
                out << payload.coreComponent.devName << std::flush;
                out.close();
            },
            .redofunc = [](UVK::TransactionPayload& payload)
            {
                std_filesystem::remove(std_filesystem::path(payload.coreComponent.name));
            },
            .transactionPayload =
            {
                .coreComponent =
                {
                    .name = selectedFile.string(),
                    .devName = buf
                }
            }
        };
        UVK::StateTracker::push(transaction);
    }

    selectedFile.clear();
}

UVK::Texture* Filesystem::selectTextures(UVK::Texture* textures, const std_filesystem::path& path, std::vector<UVK::Texture>& previews, volatile bool& bPreviews, const int& currentIndex, volatile bool& bLoad)
{
    // Constants for the file extensions
    constexpr const char* audioExtensions[] = { ".wav", ".flac", ".m4a", ".ogg", ".mp3" };
    constexpr const char* imageExtensions[] = { ".jpeg", ".jpg", ".tiff", ".gif", ".bmp", ".png", ".tga", ".psd", ".pic" };
    constexpr const char* videoExtensions[] = { ".mov", ".m4v", ".mp4", ".mpeg", ".mkv", ".mpg", ".wmv", ".webm" };
    constexpr const char* objExtensions[] = { ".obj", ".fbx", ".glb", ".gltf", ".mp3" };
    constexpr const char* codeExtensions[] = { ".yaml", ".uvklevel", ".yml" };

    for (const auto& b : audioExtensions)
        if (path.filename().extension().string() == b)
            return &textures[FS_ICON_AUDIO];

    for (const auto& b : imageExtensions)
    {
        if (path.filename().extension().string() == b)
        {
            if (bPreviews)
            {
                if (bLoad)
                {
                    previews[currentIndex] = UVK::Texture(path.string());
                    previews[currentIndex].loadImgui();
                    return &previews[currentIndex];
                }
                return &previews[currentIndex];
            }
            else return &textures[FS_ICON_IMAGE];
        }
    }

    for (const auto& b : videoExtensions)
        if (path.filename().extension().string() == b)
            return &textures[FS_ICON_VIDEO];

    for (const auto& b : objExtensions)
        if (path.filename().extension().string() == b)
            return &textures[FS_ICON_MODEL];

    for (const auto& b : codeExtensions)
        if (path.filename().extension().string() == b)
            return &textures[FS_ICON_CODE];

    if (path.filename().extension().string() == ".ttf")
        return &textures[FS_ICON_CODE];

    return &textures[FS_ICON_UNKNOWN];
}
#endif
#endif