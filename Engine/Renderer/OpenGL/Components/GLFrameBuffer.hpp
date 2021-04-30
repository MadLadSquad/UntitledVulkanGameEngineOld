// GLFrameBuffer.hpp
// Last update 4/13/2021 by Madman10K
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


        void useFramebuffer() const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        }

        static void unbindFramebuffer()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void destroyFramebuffer()
        {
            glDeleteFramebuffers(1, &FBO);
        }

        [[nodiscard]] uint32_t getFramebuffer() const
        {
            return FBO;
        }

        [[nodiscard]] uint32_t getFramebufferTexture() const
        {
            return framebufferTexture;
        }

        void init(int width, int height);

    private:
        uint32_t FBO = 0;
        uint32_t framebufferTexture = 0;
    };
}