// GLRenderer.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <utility>
#include "../EditorUI/Editor.hpp"
#include "Components/GLFrameBuffer.hpp"
#include "Engine/Renderer/Window/Window.hpp"
#include "UVKLog.h"

namespace UVK
{
    class Level;

    /**
     * @brief The OpenGL renderer
     */
    class GLRenderer
    {
    public:
        GLRenderer() = delete;

        explicit GLRenderer(Level* level, const bool& bUsesEditor, std::string theme)
        {
            bEditor = bUsesEditor;
            colTheme = std::move(theme);
            createWindow(level);
        }

        void createWindow(Level* level) noexcept;
    private:
        void renderEditor();
        void initEditor();

        FVector4 colour{};
        glm::mat4 projection{};
        GLFrameBuffer fb;
        bool bEditor;
        std::string colTheme;

        UVK::Editor ed;
    };
}