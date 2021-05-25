// VKMesh.hpp
// Last update 25/5/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <vulkan/vulkan.h>

namespace UVK
{
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