// VKFramebuffer.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif
#include "../../Textures/Texture.hpp"

namespace UVK
{
    /**
     * @brief Vulkan specific framebuffer class
     */
    class VKFramebuffer
    {
    public:
        void init(int width, int height);
        void use();
        Texture getTexture();
    private:
    };
}
