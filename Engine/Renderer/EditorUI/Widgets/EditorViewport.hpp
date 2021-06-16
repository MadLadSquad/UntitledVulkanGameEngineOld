// EditorViewport.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include "Engine/Renderer/OpenGL/Components/GLFrameBuffer.hpp"
#include "Engine/Renderer/OpenGL/Components/GLCamera.hpp"

#ifndef PRODUCTION
/**
 * @brief Displays the editor viewport is a widget containing a framebuffer
 */
namespace EditorViewport
{
    void display(UVK::GLFrameBuffer& fb, int& viewportWidth, int& viewportHeight, bool& bShow, UVK::GLCamera& camera, UVK::Actor& entity, glm::mat4& projection);
}
#endif