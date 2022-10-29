#include <GL/glew.h>
#include "GLFrameBuffer.hpp"

UVK::GLFrameBuffer::GLFrameBuffer(int width, int height)
{
    init(width, height);
}

uint32_t UVK::GLFrameBuffer::getFramebuffer() const
{
    return FBO;
}

uint32_t UVK::GLFrameBuffer::getFramebufferTexture() const
{
    return framebufferTexture;
}

void UVK::GLFrameBuffer::init(int width, int height)
{
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::log("Could not create framebuffer", UVK_LOG_TYPE_ERROR);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void UVK::GLFrameBuffer::unbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void UVK::GLFrameBuffer::destroyFramebuffer()
{
    glDeleteFramebuffers(1, &FBO);
}

void UVK::GLFrameBuffer::useFramebuffer() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}