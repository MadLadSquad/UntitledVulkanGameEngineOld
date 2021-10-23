// TopToolbar.hpp
// Last update 17/10/2021 by Madman10K
#pragma once
#include "Engine/Renderer/Textures/Texture.hpp"

#ifndef PRODUCTION

namespace UVK
{
    class EditorModuleManager;
}
/**
 * @brief Displays the toolbar widget which currently can only play the game in standalone
 */
namespace TopToolbar
{
    bool display(UVK::Texture& play, const std::string& projectName, const UVK::EditorModuleManager& modules, bool& bShow);
}
#endif