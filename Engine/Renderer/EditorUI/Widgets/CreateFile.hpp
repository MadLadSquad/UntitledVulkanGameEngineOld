// CreateFile.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <iostream>
#include <Renderer/Textures/Texture.hpp>
#include <imgui.h>

#ifndef PRODUCTION
namespace CreateFile
{
    // Creates a file
    void display(short& selectedFile, std::string& fileOutLocation, bool& bShowCreateFile1, UVK::Texture& insert, const std::string& cpFileLoc);
}
#endif