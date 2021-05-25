// VKCamera.cpp
// Last update 25/5/2021 by Madman10K
#include "VKCamera.hpp"

UVK::VKCamera::VKCamera(UVK::FVector position, UVK::FVector up, float yaw, float pitch, float movementSpeed, float turnSpeed)
{
    this->position = position;
    worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    front = FVector(0.0f, 0.0f, -1.0f);

    moveSpeed = movementSpeed;
    this->turnSpeed = turnSpeed;

    recalculate();
}

glm::mat4 UVK::VKCamera::calculateViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

float UVK::VKCamera::getYaw() const
{
    return yaw;
}

float UVK::VKCamera::getPitch() const
{
    return pitch;
}

float UVK::VKCamera::getMovementSpeed() const
{
    return moveSpeed;
}

float UVK::VKCamera::getTurnSpeed() const
{
    return turnSpeed;
}

UVK::FVector UVK::VKCamera::getPosition()
{
    return position;
}

void UVK::VKCamera::recalculate()
{
    front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
