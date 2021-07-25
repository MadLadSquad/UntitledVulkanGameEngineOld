// Projection.hpp
// Last update 25/7/2021 by Madman10K
#include "Projection.hpp"

glm::mat4& UVK::Projection::data()
{
    return projection;
}

UVK::Projection::Projection(float fov, float ratio, UVK::FVector2 planes)
{
    FOV = fov;
    aspectRatioI = ratio;
    plane = planes;
}

float& UVK::Projection::fov()
{
    return FOV;
}

float& UVK::Projection::aspectRatio()
{
    return aspectRatioI;
}

UVK::FVector2& UVK::Projection::planes()
{
    return plane;
}

void UVK::Projection::recalculateLH()
{
    projection = glm::perspectiveLH(FOV, aspectRatioI, plane.x, plane.y);
}

void UVK::Projection::recalculateRH()
{
    projection = glm::perspectiveRH(FOV, aspectRatioI, plane.x, plane.y);
}
