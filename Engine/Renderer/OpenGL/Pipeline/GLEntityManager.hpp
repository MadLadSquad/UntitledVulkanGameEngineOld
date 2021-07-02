// GLEntityManager.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Renderer/Camera/Camera.hpp>
#include <Renderer/Textures/Texture.hpp>

namespace UVK
{
    class GLEntityManager
    {
    public:
        GLEntityManager() = delete;
    private:
        friend class GLPipeline;

        static void tick(Camera* camera);
        static void clean();
    };
}
