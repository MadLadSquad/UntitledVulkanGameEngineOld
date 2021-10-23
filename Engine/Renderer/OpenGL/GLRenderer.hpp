// GLRenderer.hpp
// Last update 6/7/2021 by Madman10K
#pragma once
#include <Core/Types.hpp>

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

        explicit GLRenderer(Level* level, const bool& bUsesEditor, UVK::String theme);
        void start(Level* level) const noexcept;

        bool bEditor;
        UVK::String colTheme;
    };
}