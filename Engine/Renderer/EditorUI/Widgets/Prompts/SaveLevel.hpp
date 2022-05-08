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
    bool display(bool& bOpen, UVK::FString& location, UVK::FVector4& colour) noexcept;
}
#endif