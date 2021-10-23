// SaveLevel.hpp
// Last update 17/10/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef PRODUCTION
#include <Renderer/Textures/Texture.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

namespace UVK
{
    class Level;
}

namespace SaveLevel
{
    // Displays the SaveLevel widget
    bool display(bool& bOpen, std::string& location, UVK::FVector4& colour);
}
#endif