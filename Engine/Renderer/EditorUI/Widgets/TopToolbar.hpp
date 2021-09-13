// TopToolbar.hpp
// Last update 13/9/2021 by Madman10K
#pragma once
#include "Engine/Renderer/Textures/Texture.hpp"

#ifndef PRODUCTION
/**
 * @brief Displays the toolbar widget which currently can only play the game in standalone
 */
namespace TopToolbar
{
    void display(UVK::Texture& play, const std::string& projectName, bool& bShow);
}
#endif