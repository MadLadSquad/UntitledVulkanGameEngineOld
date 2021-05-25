// Camera.cpp
// Last update 25/5/2021 by Madman10K
#pragma once
#include "../OpenGL/Components/GLCamera.hpp"
#include "../Vulkan/Components/VKCamera.hpp"

namespace UVK
{
    class Camera
    {
    public:
        Camera(bool bUsingEditor, bool bUsesVulkan);

        Camera(bool bUsingEditor, bool bUsesVulkan, FVector position, FVector up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed);

        void init(FVector position, FVector up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed);

        template<class T>
        T& getInternal()
        {
            if (bVulkan)
            {
                return vkCamera;
            }
            return camera;
        }
    private:
        bool bEditor{};
        bool bVulkan{};

        GLCamera camera;
        VKCamera vkCamera;
    };
}