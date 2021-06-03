// TopToolbar.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include "Engine/Renderer/Textures/Texture.hpp"

/**
 * @brief Displays the toolbar widget which currently can only play the game in standalone
 */
namespace TopToolbar
{
    void display(UVK::Texture& play, bool& bShow);
}
