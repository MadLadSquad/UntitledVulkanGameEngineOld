// EditorViewport.hpp
// Last update 21/5/2021 by Madman10K
#pragma once
#include "Engine/Renderer/OpenGL/Components/GLFrameBuffer.hpp"
#include "Engine/Renderer/OpenGL/Components/GLCamera.hpp"

namespace EditorViewport
{
    void display(UVK::GLFrameBuffer& fb, int& viewportWidth, int& viewportHeight, bool& bShow, UVK::GLCamera& camera, UVK::Actor& entity, glm::mat4& projection);
}