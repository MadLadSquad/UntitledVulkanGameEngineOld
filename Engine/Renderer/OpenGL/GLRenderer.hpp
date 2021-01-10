// GLRenderer.hpp
// Last update 1/10/2021 by Madman10K
#pragma once
#include <Core.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include "../glfw/include/GLFW/glfw3.h"
#include "UVKLog.h"


namespace UVK
{
    class GLRenderer
    {
    public:
        void createWindow();
        void createTriangle();
        void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
        void compileShaders();

        GLFWwindow* window;
    };
}