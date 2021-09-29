// About.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include "Engine/Renderer/Textures/Texture.hpp"

/**
 * @brief Displays the about us widget
 */
namespace About
{
    void display(std::string& engineVersion, std::string& projectName, std::string& projectVersion, UVK::Texture& logo, bool& bShow);
}
#endif