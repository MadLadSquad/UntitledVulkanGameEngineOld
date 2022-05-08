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
    bool display(UVK::Texture& play, const UVK::FString& projectName, const UVK::EditorModuleManager& modules, bool& bShow, UVK::Texture& restart, UVK::Texture& stop) noexcept;
    void startProcess(const UVK::FString& projectName, uexec::ScriptRunner& runner, bool& bShowPlay) noexcept;
}
#endif