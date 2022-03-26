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
    bool display(std_filesystem::path& pt, UVK::Texture* textures, UVK::FilesystemWidgetData& data, bool& bShow) noexcept;
    void createFile(const std_filesystem::path& pt) noexcept;
    void createFolder(const std_filesystem::path& pt) noexcept;
    void deleteFile(std_filesystem::path& pt, std_filesystem::path& selectedFile) noexcept;
    UVK::Texture* selectTextures(UVK::Texture* textures, const std_filesystem::path& path, std::vector<UVK::Texture>& previews, volatile bool& bPreviews, const int& currentIndex, volatile bool& bLoad) noexcept;
}
#endif
#endif