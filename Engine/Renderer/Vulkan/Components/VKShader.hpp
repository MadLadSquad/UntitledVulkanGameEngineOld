// VKShader.hpp
// Last update 25/5/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

namespace UVK
{
    class VKShader
    {
    public:
        VKShader() = default;

        void createShader();
        void useShader();
    private:

    };
}
