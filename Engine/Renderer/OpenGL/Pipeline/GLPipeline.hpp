// GLPipeline.hpp
// Last update 6/7/2021 by Madman10K
#pragma once
#include <Renderer/OpenGL/Components/GLFrameBuffer.hpp>
#include <Renderer/EditorUI/Editor.hpp>
#include <Renderer/UI/UI.hpp>

namespace UVK
{
    class GLPipeline
    {
    public:
        GLPipeline() = delete;
    private:
        friend class GLRenderer;
        GLPipeline(bool bHasEditor, Level* lvl);

        void tick();
        void end();

        static void enableFeatures();
        void begin(bool bHasEditor, Level* lvl);

        bool bEditor{};

        GLfloat deltaTime{};
        GLfloat lastTime = 0;

        GLFrameBuffer fb;
        Editor ed;

        UVK::String colTheme;
#ifdef DEVELOPMENT
        Texture tx;
#endif
    };
}