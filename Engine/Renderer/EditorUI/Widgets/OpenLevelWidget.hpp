// OpenLevelWidget.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <iostream>
#include <Core.hpp>
#include <Renderer/Textures/Texture.hpp>

#ifndef PRODUCTION
namespace OpenLevelWidget
{
    // Opens a level
    void display(std::string& openLevel, bool& bShowOpenLevelWidget, double& dr, UVK::FVector4& colour, std::string& name, UVK::Texture& insert, const std::string& cpFileLoc);
}
#endif