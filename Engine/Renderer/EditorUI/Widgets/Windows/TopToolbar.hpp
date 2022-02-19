// TopToolbar.hpp
// Last update 18/2/2022 by Madman10K
#pragma once
#include "Engine/Renderer/Textures/Texture.hpp"

#ifndef PRODUCTION

namespace UVK
{
    class EditorModuleManager;
}
namespace uexec
{
    class ScriptRunner;
}

/**
 * @brief Displays the toolbar widget which currently can only play the game in standalone
 */
namespace TopToolbar
{
    bool display(UVK::Texture& play, const std::string& projectName, const UVK::EditorModuleManager& modules, bool& bShow, UVK::Texture& restart, UVK::Texture& stop);
    void startProcess(const std::string& projectName, uexec::ScriptRunner& runner, bool& bShowPlay);
}
#endif