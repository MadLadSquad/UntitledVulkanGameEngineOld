// Camera.cpp
// Last update 19/6/2021 by Madman10K
#include "Camera.hpp"
#include <Renderer/RendererResources.hpp>

UVK::Camera::Camera(UVK::FVector position, UVK::FVector up, UVK::FVector rot)
{
    init(position, up, rot);
}

void UVK::Camera::init(UVK::FVector pos, UVK::FVector upP, UVK::FVector rot)
{
    res.position = pos;
    res.worldUp = upP;
    res.rotation = rot;
    res.front = FVector(0.0f, 0.0f, -1.0f);

    recalculate();
}

UVK::CameraResources& UVK::Camera::data()
{
    return res;
}

glm::mat4 UVK::Camera::calculateViewMatrixRH() const
{
    if (rendererResources.bUsesVulkan)
    {
        return glm::lookAtRH(FVector(res.position.x, -res.position.y, res.position.z), FVector(res.position.x, -res.position.y, res.position.z) + FVector(res.front.x, -res.front.y, res.front.z), FVector(res.up.x, -res.up.y, res.up.z));
    }

    return glm::lookAtRH(res.position, res.position + res.front, res.up);
}

glm::mat4 UVK::Camera::calculateViewMatrixLH() const
{
    if (rendererResources.bUsesVulkan)
    {
        return glm::lookAtLH(FVector(res.position.x, -res.position.y, res.position.z), FVector(res.position.x, -res.position.y, res.position.z) + FVector(res.front.x, -res.front.y, res.front.z), FVector(res.up.x, -res.up.y, res.up.z));
    }

    return glm::lookAtLH(res.position, res.position + res.front, res.up);
}

void UVK::Camera::recalculate()
{
    if (rendererResources.bUsesVulkan)
    {
        res.front.x = glm::cos(glm::radians(res.rotation.x)) * glm::cos(glm::radians(-res.rotation.y));
        res.front.y = glm::sin(glm::radians(-res.rotation.y));
        res.front.z = glm::sin(glm::radians(res.rotation.x)) * glm::cos(glm::radians(-res.rotation.y));
        res.front = glm::normalize(FVector(res.front.x, -res.front.y, res.front.z));

        res.right = glm::normalize(glm::cross(FVector(res.front.x, -res.front.y, res.front.z), FVector(res.worldUp.x, -res.worldUp.y, res.worldUp.z)));
        res.up = glm::normalize(glm::cross(FVector(res.right.x, -res.right.y, res.right.z), FVector(res.front.x, -res.front.y, res.front.z)));
    }
    else
    {
        res.front.x = glm::cos(glm::radians(res.rotation.x)) * glm::cos(glm::radians(res.rotation.y));
        res.front.y = glm::sin(glm::radians(res.rotation.y));
        res.front.z = glm::sin(glm::radians(res.rotation.x)) * glm::cos(glm::radians(res.rotation.y));
        res.front = glm::normalize(res.front);

        res.right = glm::normalize(glm::cross(res.front, res.worldUp));
        res.up = glm::normalize(glm::cross(res.right, res.front));
    }
}

UVK::Projection& UVK::Camera::getProjection()
{
    return res.projection;
}