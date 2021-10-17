// Filesystem.hpp
// Last update 12/8/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef PRODUCTION
#include "Engine/Renderer/Textures/Texture.hpp"
#ifndef __MINGW32__

/**
 * @brief A filesystem widget with formatting for different file types
 */
namespace Filesystem
{
    struct Preview
    {
        Preview() = default;

        UVK::String location;
        UVK::Texture texture;
    };

    bool display(std_filesystem::path& pt, UVK::Texture* textures, bool& bShow);
    void createFile(const std_filesystem::path& pt);
    void createFolder(const std_filesystem::path& pt);
    void deleteFile(std_filesystem::path& pt, std_filesystem::path& selectedFile);
    UVK::Texture* selectTextures(UVK::Texture* textures, const std_filesystem::path& path, std::vector<UVK::Texture>& previews, volatile bool& bPreviews, const int& currentIndex, volatile bool& bLoad);
}
#endif
#endif