#include "Projection.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4& UVK::Projection::data() noexcept
{
    return projection;
}

UVK::Projection::Projection(float fov, float ratio, UVK::FVector2 planes) noexcept
{
    FOV = fov;
    aspectRatioI = ratio;
    plane = planes;
}

float& UVK::Projection::fov() noexcept
{
    return FOV;
}

float& UVK::Projection::aspectRatio() noexcept
{
    return aspectRatioI;
}

UVK::FVector2& UVK::Projection::planes() noexcept
{
    return plane;
}

void UVK::Projection::recalculateLH() noexcept
{
    projection = glm::perspectiveLH(glm::radians(FOV), aspectRatioI, plane.x, plane.y);
}

void UVK::Projection::recalculateRH() noexcept
{
    projection = glm::perspectiveRH(glm::radians(FOV), aspectRatioI, plane.x, plane.y);
}
