// CreateFile.hpp
// Last update 18/2/2022 by Madman10K
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