#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include "Engine/Renderer/Textures/Texture.hpp"

/**
 * @brief Displays the about us widget
 */
namespace About
{
    void display(std::string& engineVersion, std::string& projectName, std::string& projectVersion, UVK::Texture& logo, bool& bShow) noexcept;
}
#endif