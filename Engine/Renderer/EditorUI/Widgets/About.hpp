// About.hpp
// Last update 4/28/2021 by Madman10K
#pragma once
#include "Engine/Renderer/Textures/Texture.hpp"
#include <imgui.h>

namespace About
{
    void display(std::string& engineVersion, std::string& projectName, std::string& projectVersion, UVK::Texture& logo, bool& bShow);
}