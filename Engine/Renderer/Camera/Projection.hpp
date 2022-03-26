#pragma once
#include <Core/Types.hpp>

namespace UVK
{
    class UVK_PUBLIC_API Projection
    {
    public:
        Projection() = default;
        Projection(float fov, float ratio, FVector2 planes) noexcept;

        glm::mat4& data() noexcept;

        float& fov() noexcept;
        float& aspectRatio() noexcept;

        // x - near, y - far
        FVector2& planes() noexcept;

        void recalculateLH() noexcept;
        void recalculateRH() noexcept;
    private:
        float FOV = 90;
        float aspectRatioI{};
        FVector2 plane = { 0.1f, 100.0f };

        glm::mat4 projection{};
    };
}