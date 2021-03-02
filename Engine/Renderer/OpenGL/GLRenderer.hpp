// GLRenderer.hpp
// Last update 3/2/2021 by Madman10K
#pragma once

#include <GL/glew.h>
#include "Components/GLMesh.hpp"
#include "Components/GLShader.hpp"
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

        explicit GLRenderer(Level* level, bool& bUsesEditor)
        {
            bEditor = bUsesEditor;

            createWindow(level);
        }

        void createWindow(Level* level) noexcept;
        static void createTriangle();
        //void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
        //void compileShaders();
    private:
        Actor selectedEntity;
        bool bShowOpenLevelWidget= false;
        bool bSetBuff = false;
        bool bShowSaveLevelWidget = false;
        bool bEditor;

        static void setDarkTheme();
    };
}