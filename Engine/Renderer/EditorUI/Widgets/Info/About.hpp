#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include "Engine/Renderer/Textures/Texture.hpp"

/**
 * @brief Displays the about us widget
 */
namespace About
{
    void display(UVK::FString& engineVersion, UVK::FString& projectName, UVK::FString& projectVersion, UVK::Texture& logo, bool& bShow) noexcept;
}
#endif