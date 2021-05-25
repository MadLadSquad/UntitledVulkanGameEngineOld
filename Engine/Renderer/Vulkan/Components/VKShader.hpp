// VKShader.hpp
// Last update 25/5/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <vulkan/vulkan.h>

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