// GLEntityManager.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <Renderer/Camera/Camera.hpp>
#include <Renderer/Textures/Texture.hpp>

namespace UVK
{
    class UVK_PUBLIC_API GLEntityManager
    {
    public:
        GLEntityManager() = delete;
    private:
        friend class GLPipeline;

        static void tick(Camera* camera);
        static void clean();
    };
}
