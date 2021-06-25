// Camera.cpp
// Last update 19/6/2021 by Madman10K
#pragma once
#include "Projection.hpp"

namespace UVK
{
    struct CameraResources
    {
        Projection projection;

        FVector position{};
        FVector front{};
        FVector up{};
        FVector right{};
        FVector worldUp{};
        FVector rotation{};
    };

    /**
     * @brief A cross-renderer camera abstraction
     */
    class Camera
    {
    public:
        Camera() = default;
        Camera(FVector position, FVector up, FVector rot);

        void init(FVector position, FVector up, FVector rot);

        CameraResources& data();

        [[nodiscard]] glm::mat4 calculateViewMatrixRH() const;
        [[nodiscard]] glm::mat4 calculateViewMatrixLH() const;

        void recalculate();

        Projection& getProjection();
    private:
        CameraResources res;
    };
}