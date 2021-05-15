// EditorViewport.hpp
// Last update 15/5/2021 by Madman10K
#pragma once
#include "Engine/Renderer/OpenGL/Components/GLFrameBuffer.hpp"

namespace EditorViewport
{
    void display(UVK::GLFrameBuffer& fb, int& viewportWidth, int& viewportHeight, bool& bShow);
}