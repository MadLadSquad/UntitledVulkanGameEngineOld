// GLRenderer.hpp
// Last update 6/7/2021 by Madman10K
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
    private:
        friend class Renderer;

        explicit GLRenderer(Level* level, const bool& bUsesEditor, UVK::String theme)
        {
            bEditor = bUsesEditor;
            colTheme = std::move(theme);
            start(level);
        }
        void start(Level* level) const noexcept;

        bool bEditor;
        UVK::String colTheme;
    };
}