// CreateFile.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <iostream>
#include <Renderer/Textures/Texture.hpp>
#include <imgui.h>

#ifndef PRODUCTION
namespace CreateFile
{
    // Creates a file
    void display(uint8_t& selectedFile, std::string& fileOutLocation, bool& bShowCreateFile1, UVK::Texture& insert, const std::string& cpFileLoc);
}
#endif