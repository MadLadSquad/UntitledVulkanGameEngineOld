// GLRenderer.hpp
// Last update 1/10/2021 by Madman10K
#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "../glfw/include/GLFW/glfw3.h"
#include <Core.hpp>
#include "UVKLog.h"
#include "Engine/Renderer/Window/Window.hpp"



namespace UVK
{
    class Level;

    class GLRenderer
    {
    public:
        void createWindow(Level* level);
        void createTriangle();
        void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
        void compileShaders();
        void setDarkTheme();
    };
}