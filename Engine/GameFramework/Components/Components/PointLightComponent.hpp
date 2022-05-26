#pragma once
#include <Core/Types.hpp>

namespace UVK
{
    enum PointLightState
    {
        POINT_LIGHT_STATE_DYNAMIC,      // Fully dynamic lighting, only 4096 lights as defined by the VK_MAX_DYNAMIC_POINT_LIGHTS
        POINT_LIGHT_STATE_STATIONARY,   // Just like in Unreal Engine 4
        POINT_LIGHT_STATE_STATIC
    };

    struct UVK_PUBLIC_API PointLightComponent
    {
        // X - R
        // Y - G
        // Z - B
        // W - Intensity
        FVector4 colour = { 1.0f, 1.0f, 1.0f, 1.0f };
        FVector translationOffset = { 0.0f, 0.0f, 0.0f };
        PointLightState state = POINT_LIGHT_STATE_STATIONARY;
    };

    struct UVK_PUBLIC_API DirectionalLightComponent
    {

    };
}