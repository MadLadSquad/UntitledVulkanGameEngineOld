// EditorViewport.hpp
// Last update 30/6/2021 by Madman10K
#pragma once
#include "Engine/Renderer/OpenGL/Components/GLFrameBuffer.hpp"
#include "Engine/Renderer/Camera/Camera.hpp"


#ifndef PRODUCTION
namespace UVK
{
    class Actor;
}
/**
 * @brief Displays the editor viewport is a widget containing a framebuffer
 */
namespace EditorViewport
{
    void display(UVK::GLFrameBuffer& fb, int& viewportWidth, int& viewportHeight, bool& bShow, UVK::Camera& camera, UVK::Actor& entity, glm::mat4& projection);
}
#endif