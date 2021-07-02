// WorldSettings.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <Renderer/Textures/Texture.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

#ifndef PRODUCTION
/**
 * @brief Displays the world settings which manages all data that is specific to a given level
 */
namespace WorldSettings
{
    void display(UVK::FVector4& colour, UVK::FVector4& ambientLight, std::string& name, bool& bShow, UVK::Texture& insert, const std::string& cpFileLoc);
}
#endif