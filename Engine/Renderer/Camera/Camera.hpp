// Camera.cpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include "Projection.hpp"

namespace UVK
{
    /**
     * @brief A cross-renderer camera abstraction
     */
    class Camera
    {
    public:
        Camera() = default;
        Camera(FVector position, FVector up, FVector rot);

        void init(FVector position, FVector up, FVector rot);

        [[nodiscard]] glm::mat4 calculateViewMatrixRH() const;
        [[nodiscard]] glm::mat4 calculateViewMatrixLH() const;

        void recalculate();

        Projection& getProjection();

        FVector position{};
        FVector front{};
        FVector up{};
        FVector right{};
        FVector worldUp{};
        FVector rotation{};
    private:
        Projection projection;
    };
}