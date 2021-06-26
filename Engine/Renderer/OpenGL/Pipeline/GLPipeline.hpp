// GLPipeline.hpp
// Last update 26/6/2021 by Madman10K
#pragma once
#include <Renderer/OpenGL/Components/GLFrameBuffer.hpp>
#include <Renderer/EditorUI/Editor.hpp>

namespace UVK
{
    //class Level;

    class GLPipeline
    {
    public:
        GLPipeline(bool bHasEditor, Level* lvl);

        void tick();
        void end();
    private:
        static void enableFeatures();
        void initEditor();
        void begin(bool bHasEditor, Level* lvl);

        bool bEditor{};

        GLfloat deltaTime{};
        GLfloat lastTime = 0;

        GLFrameBuffer fb;
        Editor ed;
        Level* level{};

        UVK::String colTheme;
#ifdef DEVELOPMENT
        Texture tx;
#endif
    };
}