// Projection.hpp
// Last update 14/6/2021 by Madman10K
#include "Projection.hpp"

glm::mat4& UVK::Projection::data()
{
    return projection;
}

UVK::Projection::Projection(float fov, float ratio, UVK::FVector2 planes)
{
    FOV = fov;
    aspectRatio = ratio;
    plane = planes;

    projection = glm::perspective(FOV, aspectRatio, plane.x, plane.y);
}

float& UVK::Projection::getFOV()
{
    return FOV;
}

float& UVK::Projection::getAspectRatio()
{
    return aspectRatio;
}

UVK::FVector2& UVK::Projection::getPlanes()
{
    return plane;
}

void UVK::Projection::recalculate()
{
    projection = glm::perspective(FOV, aspectRatio, plane.x, plane.y);
}
