// GLRenderer.hpp
// Last update 3/17/2021 by Madman10K
#pragma once

//#include <GL/glew.h>
//#include "Components/GLMesh.hpp"
//#include "Components/GLShader.hpp"
#include <Core.hpp>
#include "Engine/Renderer/Window/Window.hpp"
#include "UVKLog.h"




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
    private:
        Actor selectedEntity;
        bool bShowOpenLevelWidget= false;
        bool bSetBuff = false;
        bool bShowSaveLevelWidget = false;
        bool bEditor;

        static void setDarkTheme();
    };
}