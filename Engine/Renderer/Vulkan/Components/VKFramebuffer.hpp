// VKFramebuffer.hpp
// Last update 25/5/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <vulkan/vulkan.h>
#include "../../Textures/Texture.hpp"

namespace UVK
{
    class VKFramebuffer
    {
    public:
        void init(int width, int height);
        void use();
        Texture getTexture();
    private:
    };
}