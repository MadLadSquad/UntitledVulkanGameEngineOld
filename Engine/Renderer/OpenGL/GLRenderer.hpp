// GLRenderer.hpp
// Last update 3/27/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "Components/GLFrameBuffer.hpp"
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

        void renderEditor(Texture& play);
        void initEditor() const;

        void loadResources();

        static void setDarkTheme();

        FVector4 colour{};

        std::string levelName;
        std::string openLevel;
        std::string location;
        std::string name;
        std::string fileOutLocation;
        glm::mat4 projection{};

        GLFrameBuffer fb;

        int wWidth, wHeight;

        bool bShowCreateFile1 = false;
        short selectedFile = 0;
    };
}