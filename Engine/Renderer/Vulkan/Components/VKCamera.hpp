// VKCamera.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#endif
namespace UVK
{
    /**
     * @brief Vulkan specific camera class
     */
    class VKCamera
    {
    public:
        VKCamera() = default;
        VKCamera(FVector position, FVector up, float yaw, float pitch, float movementSpeed, float turnSpeed);

        glm::mat4 calculateViewMatrix();

        [[nodiscard]] float getYaw() const;
        [[nodiscard]] float getPitch() const;
        [[nodiscard]] float getMovementSpeed() const;
        [[nodiscard]] float getTurnSpeed() const;

        FVector getPosition();
    private:
        FVector position{};
        FVector front{};
        FVector up{};
        FVector right{};
        FVector worldUp{};

        float yaw = 0;
        float pitch = 0;

        float moveSpeed = 0;
        float turnSpeed = 0;

        void recalculate();
    };
}
