// Camera.cpp
// Last update 25/7/2021 by Madman10K
#include "Camera.hpp"
#include <Engine/Core/Core/Global.hpp>

UVK::Camera::Camera(UVK::FVector position, UVK::FVector up, UVK::FVector rot)
{
    init(position, up, rot);
}

void UVK::Camera::init(UVK::FVector pos, UVK::FVector upP, UVK::FVector rot)
{
    position = pos;
    worldUp = upP;
    rotation = rot;
    front = FVector(0.0f, 0.0f, -1.0f);
    recalculate();
}

glm::mat4 UVK::Camera::calculateViewMatrixRH() const
{
    if (global.bUsesVulkan)
    {
        return glm::lookAtRH(FVector(position.x, -position.y, position.z), FVector(position.x, -position.y, position.z) + FVector(front.x, -front.y, front.z), FVector(up.x, -up.y, up.z));
    }

    return glm::lookAtRH(position, position + front, up);
}

glm::mat4 UVK::Camera::calculateViewMatrixLH() const
{
    if (global.bUsesVulkan)
    {
        return glm::lookAtLH(FVector(position.x, -position.y, position.z), FVector(position.x, -position.y, position.z) + FVector(front.x, -front.y, front.z), FVector(up.x, -up.y, up.z));
    }

    return glm::lookAtLH(position, position + front, up);
}

void UVK::Camera::recalculate()
{
    if (global.bUsesVulkan)
    {
        front.x = glm::cos(glm::radians(rotation.x)) * glm::cos(glm::radians(-rotation.y));
        front.y = glm::sin(glm::radians(-rotation.y));
        front.z = glm::sin(glm::radians(rotation.x)) * glm::cos(glm::radians(-rotation.y));
        front = glm::normalize(FVector(front.x, -front.y, front.z));

        right = glm::normalize(glm::cross(FVector(front.x, -front.y, front.z), FVector(worldUp.x, -worldUp.y, worldUp.z)));
        up = glm::normalize(glm::cross(FVector(right.x, -right.y, right.z), FVector(front.x, -front.y, front.z)));
    }
    else
    {
        front.x = glm::cos(glm::radians(rotation.x)) * glm::cos(glm::radians(rotation.y));
        front.y = glm::sin(glm::radians(rotation.y));
        front.z = glm::sin(glm::radians(rotation.x)) * glm::cos(glm::radians(rotation.y));
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
}

UVK::Projection& UVK::Camera::projection()
{
    return proj;
}

UVK::Camera UVK::Camera::makeCamera(FVector position, FVector up, FVector rotation, FVector2 planes, float fov, float aspectRatio)
{
    auto camera = Camera(position, up, rotation);
    camera.projection().planes() = planes;
    camera.projection().fov() = fov;
    camera.projection().aspectRatio() = (float)aspectRatio;
    camera.projection().recalculateRH();

    return camera;
}