#include "Camera.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <Core/Actor.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

UVK::Camera::Camera(const CoreComponent& coreComponent, FVector position, FVector rot, FVector up) noexcept
{
    init(coreComponent, position, up, rot);
}

void UVK::Camera::init(const CoreComponent& coreComponent, FVector translation, FVector rotation, FVector upp) noexcept
{
    core = &coreComponent;

    translationOffset = translation;
    worldUp = upp;
    rotationOffset = rotation;
    front = FVector(0.0f, 0.0f, -1.0f);
    recalculate();
}

glm::mat4 UVK::Camera::calculateViewMatrixRH() const noexcept
{
    return glm::lookAtRH(core->translation + translationOffset, core->translation + translationOffset + front, up);
}

glm::mat4 UVK::Camera::calculateViewMatrixLH() const noexcept
{
    return glm::lookAtLH(core->translation + translationOffset, core->translation + translationOffset + front, up);
}

void UVK::Camera::recalculate() noexcept
{
    front.x = glm::cos(glm::radians(core->rotation.x + rotationOffset.x)) * glm::cos(glm::radians(core->rotation.y + rotationOffset.y));
    front.y = glm::sin(glm::radians(core->rotation.y + rotationOffset.y));
    front.z = glm::sin(glm::radians(core->rotation.x + rotationOffset.x)) * glm::cos(glm::radians(core->rotation.y + rotationOffset.y));

    //glm::mat4 roll = glm::rotate(glm::mat4(1.0f), glm::radians(core->rotation.z + rotationOffset.z), front);
    front = glm::normalize(front);
    glm::mat4 roll = glm::rotate(glm::mat4(1.0f), glm::radians(core->rotation.z + rotationOffset.z), front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));

    glm::mat3 rl(roll);
    up = rl * up;
}

UVK::Projection& UVK::Camera::projection() noexcept
{
    return proj;
}

UVK::Camera UVK::Camera::makeCamera(const CoreComponent& coreComponent, FVector position, FVector rotation, FVector up, FVector2 planes, float fov, float aspectRatio) noexcept
{
    auto camera = Camera(coreComponent, position, up, rotation);
    camera.projection().planes() = planes;
    camera.projection().fov() = fov;
    camera.projection().aspectRatio() = (float)aspectRatio;
    camera.projection().recalculateRH();

    return camera;
}