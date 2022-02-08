// Projection.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <Core/Types.hpp>

namespace UVK
{
    class UVK_PUBLIC_API Projection
    {
    public:
        Projection() = default;
        Projection(float fov, float ratio, FVector2 planes);

        glm::mat4& data();

        float& fov();
        float& aspectRatio();

        // x - near, y - far
        FVector2& planes();

        void recalculateLH();
        void recalculateRH();
    private:
        float FOV = 90;
        float aspectRatioI{};
        FVector2 plane = { 0.1f, 100.0f };

        glm::mat4 projection{};
    };
}