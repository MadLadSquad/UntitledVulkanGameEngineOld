// Camera.cpp
// Last update 25/5/2021 by Madman10K
#include "Camera.hpp"

UVK::Camera::Camera(bool bUsingEditor, bool bUsesVulkan)
{
    bEditor = bUsingEditor;
    bVulkan = bUsesVulkan;
}

UVK::Camera::Camera(bool bUsingEditor, bool bUsesVulkan, UVK::FVector position, UVK::FVector up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed)
{
    bEditor = bUsingEditor;
    bVulkan = bUsesVulkan;

    init(position, up, yaw, pitch, movementSpeed, turnSpeed);
}

void UVK::Camera::init(UVK::FVector position, UVK::FVector up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed)
{
    if (bVulkan)
    {
        vkCamera = VKCamera(position, up, yaw, pitch, movementSpeed, turnSpeed);
    }
    else
    {
        camera = GLCamera(position, up, yaw, pitch, movementSpeed, turnSpeed);
    }
}
