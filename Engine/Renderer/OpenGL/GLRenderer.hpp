// GLRenderer.hpp
// Last update 1/10/2021 by Madman10K
#pragma once

#ifdef __APPLE__
    #define NO_GLEW
#else
    #undef NO_GLEW
#endif

#ifdef NO_GLEW
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif
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
        GLRenderer() = delete;

        explicit GLRenderer(Level* level)
        {
            createWindow(level);
        }


        void createWindow(Level* level) noexcept;
        void createTriangle();
        void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
        void compileShaders();
        void setDarkTheme();

    private:
        Actor selectedEntity;
        bool bShowOpenLevelWidget;
        bool bSetBuff;
        bool bShowSaveLevelWidget;
    };
}