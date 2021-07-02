// RemoveFile.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <Renderer/Textures/Texture.hpp>
#include <imgui.h>

#ifndef PRODUCTION
namespace RemoveFile
{
    void display(bool& bShow, UVK::Texture& insert, const std::string& cpFileLoc);
}
#endif