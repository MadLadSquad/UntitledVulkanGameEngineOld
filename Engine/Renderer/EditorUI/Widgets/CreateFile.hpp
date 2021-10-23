// CreateFile.hpp
// Last update 17/10/2021 by Madman10K
#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include <iostream>
#include <Renderer/Textures/Texture.hpp>
#include <imgui.h>


namespace CreateFile
{
    // Creates a file
    bool display(std::string& fileOutLocation, bool& bShowCreateFile1);
}
#endif