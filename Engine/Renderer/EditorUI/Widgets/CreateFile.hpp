// CreateFile.hpp
// Last update 1/8/2021 by Madman10K
#pragma once
#include <iostream>
#include <Renderer/Textures/Texture.hpp>
#include <imgui.h>

#ifndef PRODUCTION
namespace CreateFile
{
    // Creates a file
    void display(std::string& fileOutLocation, bool& bShowCreateFile1);
}
#endif