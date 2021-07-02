// VKShader.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

namespace UVK
{
    /**
     * @brief Vulkan specific spirv shader class
     */
    class VKShader
    {
    public:
        VKShader() = default;

        void createShader();
        void useShader();
    private:

    };
}
