// OpenLevelWidget.hpp
// Last update 1/8/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef PRODUCTION
#include <iostream>
#include <Renderer/Textures/Texture.hpp>

namespace OpenLevelWidget
{
    // Opens a level
    bool display(std::string& openLevel, bool& bShowOpenLevelWidget, double& dr, UVK::FVector4& colour);
}
#endif