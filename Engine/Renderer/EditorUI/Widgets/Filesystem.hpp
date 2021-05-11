// Filesystem.hpp
// Last update 5/04/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "Engine/Renderer/Textures/Texture.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>
#ifndef __MINGW32__

namespace Filesystem
{
    void display(std_filesystem::path& pt, std::string& cpLoc);
}
#endif