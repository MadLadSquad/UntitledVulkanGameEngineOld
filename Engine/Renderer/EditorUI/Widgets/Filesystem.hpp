// Filesystem.hpp
// Last update 1/8/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "Engine/Renderer/Textures/Texture.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>
#ifndef PRODUCTION
#ifndef __MINGW32__

/**
 * @brief A filesystem widget with formatting for different file types
 */
namespace Filesystem
{
    void display(std_filesystem::path& pt, UVK::Texture* textures, bool& bShow);
}
#endif
#endif