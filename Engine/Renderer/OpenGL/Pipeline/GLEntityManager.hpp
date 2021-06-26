// GLEntityManager.hpp
// Last update 26/6/2021 by Madman10K
#pragma once
#include <Renderer/Camera/Camera.hpp>
#include <Renderer/Textures/Texture.hpp>

namespace UVK
{
    class GLEntityManager
    {
    public:
        static void tick(Camera* camera);
        static void clean();
    };
}
