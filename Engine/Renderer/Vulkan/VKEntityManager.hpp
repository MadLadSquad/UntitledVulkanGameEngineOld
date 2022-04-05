#pragma once

namespace UVK
{
    class Camera;

    class UVK_PUBLIC_API VKEntityManager
    {
    public:
        VKEntityManager() = delete;

    private:
        friend class VulkanRenderer;
    };
}