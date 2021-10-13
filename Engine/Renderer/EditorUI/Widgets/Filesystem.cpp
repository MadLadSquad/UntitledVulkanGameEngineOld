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
void Filesystem::display(std_filesystem::path& pt, UVK::Texture* textures, std::unordered_map<std::string, UVK::Texture>& previews, bool& bShow)
{
    // Constants for the file extensions
    constexpr const char* audioExtensions[] = { ".wav", ".flac", ".m4a", ".ogg", ".mp3" };
    constexpr const char* imageExtensions[] = { ".jpeg", ".jpg", ".tiff", ".gif", ".bmp", ".png", ".tga", ".psd", ".pic" };
    constexpr const char* videoExtensions[] = { ".mov", ".m4v", ".mp4", ".mpeg", ".mkv", ".mpg", ".wmv", ".webm" };
    constexpr const char* objExtensions[] = { ".obj", ".fbx", ".glb", ".gltf", ".mp3" };
    constexpr const char* codeExtensions[] = { ".yaml", ".uvklevel", ".yml" };

    // Variables for the UI
    static float padding = 20.0f;
    static float imageSize = 50.0f;
    float cellSize = padding + imageSize;
    static bool bUsePreviews = true;
    int columns;

    // Variables for file actions
    bool bCreateFile = false;
    bool bRemoveFile = false;
    bool bAddDirectory = false;

    // The current file represented as a string
    static std::string selectedFile;

    ImGui::Begin("Filesystem##Widget", &bShow, ImGuiWindowFlags_MenuBar);

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
                while (std_filesystem::exists(pt/("NewFolder" + std::to_string(i))))
                    i++;

                create_directory(std_filesystem::path(pt/("NewFolder" + std::to_string(i))));

                UVK::Transaction transaction =
                {
                    .undofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        remove_all(std_filesystem::path(core.name));
                    },
                    .redofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        if (!std_filesystem::exists(core.name))
                            std::filesystem::create_directory(std_filesystem::path(core.name));
                    },
                    .coreComponent =
                    {
                        .name = pt/("NewFolder" + std::to_string(i))
                    }
                };
                UVK::StateTracker::push(transaction);
            }
            else
            {
                create_directory(pt/"NewFolder");

                UVK::Transaction transaction =
                {
                    .undofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        remove_all(std_filesystem::path(core.name));
                    },
                    .redofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        if (!std_filesystem::exists(core.name))
                            std::filesystem::create_directory(std_filesystem::path(core.name));
                    },
                    .coreComponent =
                    {
                        .name = pt/"NewFolder"
                    }
                };
                UVK::StateTracker::push(transaction);
            }

            bAddDirectory = false;
        }

        if (bCreateFile)
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
                    .undofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        if (std_filesystem::exists(core.name))
                            remove(std_filesystem::path(core.name));
                    },
                    .redofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        std::ofstream out(core.name);
                        out << std::endl;
                        out.close();
                    },
                    .coreComponent =
                    {
                        .name = pt/("NewFile" + std::to_string(i) + ".txt")
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
                    .undofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        if (std_filesystem::exists(core.name))
                            remove(std_filesystem::path(core.name));
                    },
                    .redofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        std::ofstream out(core.name);
                        out << std::endl;
                        out.close();
                    },
                    .coreComponent =
                    {
                        .name = pt/"NewFile.txt"
                    }
                };
                UVK::StateTracker::push(transaction);
            }

            bCreateFile = false;
        }

        if (bRemoveFile)
        {
            if (is_directory(std_filesystem::path(selectedFile)))
            {
                // TODO: Add a warning here
                remove_all(std_filesystem::path(selectedFile));

                UVK::Transaction transaction =
                {
                    .undofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        // TODO: Recreate the whole directory structure
                        std_filesystem::create_directory(std_filesystem::path(core.name));
                    },
                    .redofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        std_filesystem::remove_all(std_filesystem::path(core.name));
                    },
                    .coreComponent =
                    {
                        .name = selectedFile
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

                remove(std_filesystem::path(selectedFile));

                UVK::Transaction transaction =
                {
                    .undofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        std::ofstream out(std_filesystem::path(core.name));
                        out << core.devName << std::flush;
                        out.close();
                    },
                    .redofunc = [](UVK::Actor&, UVK::CoreComponent& core, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
                    {
                        std_filesystem::remove(std_filesystem::path(core.name));
                    },
                    .coreComponent =
                    {
                        .name = selectedFile,
                        .devName = buf
                    }
                };
                UVK::StateTracker::push(transaction);
            }

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