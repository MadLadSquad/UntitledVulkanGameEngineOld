#pragma once
#include <Core.hpp>

namespace UVK
{
    class GLFrameBuffer
    {
    public:
        GLFrameBuffer() = default;

        GLFrameBuffer(int width, int height)
        {
            init(width, height);
        }
        unsigned int texColourBuffer = 0;

        void init(int width, int height);
        uint32_t FBO = 0;
    private:

    };
}
