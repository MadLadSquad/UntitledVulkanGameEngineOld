// WorldSettings.hpp
// Last update 5/5/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

namespace WorldSettings
{
    void display(UVK::FVector4& colour, UVK::FVector4 ambientLight, std::string& name);
}