// GLFrameBuffer.hpp
// Last update 2/9/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    /**
     * @brief OpenGL specific framebuffer class
     */
    class GLFrameBuffer
    {
    public:
        GLFrameBuffer() = default;

        GLFrameBuffer(int width, int height)
        {
            init(width, height);
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

        static void unbindFramebuffer();
        void destroyFramebuffer();
    private:
        friend class GLPipeline;

        void useFramebuffer() const;

        uint32_t FBO = 0;
        uint32_t framebufferTexture = 0;
    };
}