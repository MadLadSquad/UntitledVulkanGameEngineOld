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

    void display(std_filesystem::path& pt, UVK::Texture* textures, std::unordered_map<std::string, UVK::Texture>& previews, bool& bShow);
}
#endif
#endif