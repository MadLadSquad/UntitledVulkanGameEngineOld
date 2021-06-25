// Projection.hpp
// Last update 14/6/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    class Projection
    {
    public:
        Projection() = default;
        Projection(float fov, float ratio, FVector2 planes);

        glm::mat4& data();

        float& getFOV();
        float& getAspectRatio();

        // x - near, y - far
        FVector2& getPlanes();

        void recalculateLH();
        void recalculateRH();
    private:
        float FOV = 90;
        float aspectRatio;
        FVector2 plane = { 0.1f, 100.0f };

        glm::mat4 projection{};
    };
}