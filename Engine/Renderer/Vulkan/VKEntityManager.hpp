// GLEntityManager.hpp
// Last update 21/12/2021 by Madman10K
#pragma once

namespace UVK
{
    class Camera;

    class VKEntityManager
    {
    public:
        VKEntityManager() = delete;
    private:
        friend class VulkanRenderer;

        static void tick(Camera* camera);
        static void clean();
    };
}