#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include "Engine/Renderer/OpenGL/Components/GLFrameBuffer.hpp"
#include "Engine/Renderer/Camera/Camera.hpp"

namespace UVK
{
    class Actor;
}
/**
 * @brief Displays the editor viewport is a widget containing a framebuffer
 */
namespace EditorViewport
{
    void display(UVK::GLFrameBuffer& fb, int& viewportWidth, int& viewportHeight, bool& bShow, UVK::Camera& camera, UVK::Actor& entity, glm::mat4& projection, bool& bFocused) noexcept;
}
#endif