// Camera.cpp
// Last update 25/7/2021 by Madman10K
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

        Projection& projection();

        FVector position{};
        FVector front{};
        FVector up{};
        FVector right{};
        FVector worldUp{};
        FVector rotation{};
    private:
        Projection proj;
    };

    Camera makeCamera(FVector position = FVector(0.0f, 0.0f, 0.0f), FVector up = FVector(0.0f, 0.0f, 0.0f), FVector rotation = FVector(), FVector2 planes = FVector2(0.1f, 100.0f), float fov = 90.0f, float aspectRatio = Window::windowSize().x / Window::windowSize().y);
}