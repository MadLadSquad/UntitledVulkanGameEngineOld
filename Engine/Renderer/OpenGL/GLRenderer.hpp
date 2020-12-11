// PlayerController.hpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include <Core.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include "../glfw/include/GLFW/glfw3.h"



namespace UVK
{
    class GLRenderer
    {
    public:
        void CreateWindow();
        void CreateTriangle();
        void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
        void CompileShaders();

        GLFWwindow* window;
    };
}