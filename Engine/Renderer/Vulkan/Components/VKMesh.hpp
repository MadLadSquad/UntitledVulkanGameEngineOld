// VKMesh.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif

namespace UVK
{
    /**
     * @brief Vulkan specific mesh class
     */
    class VKMesh
    {
    public:
        VKMesh() = default;
        void create();
        void render();
        void clear();
    private:

    };
}
