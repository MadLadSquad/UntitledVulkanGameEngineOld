// OpenLevelWidget.hpp
// Last update 1/8/2021 by Madman10K
#pragma once
#include <iostream>
#include <Core.hpp>
#include <Renderer/Textures/Texture.hpp>

#ifndef PRODUCTION
namespace OpenLevelWidget
{
    // Opens a level
    void display(std::string& openLevel, bool& bShowOpenLevelWidget, double& dr, UVK::FVector4& colour);
}
#endif