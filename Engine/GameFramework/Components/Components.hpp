// Components.hpp
// Last update 1/10/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    UVK_API struct CoreComponent
    {
        std::string name;
        uint64_t id;
    };

    UVK_API struct MeshComponent
    {
        glm::mat4 model;
        FVector translation;
        FVector scale;
        FVector rotation;
        float degrees;
    };

    UVK_API struct PointLightComponent
    {

    };

    UVK_API struct SpotlightComponent
    {

    };

    UVK_API struct DirectionalLightComponent
    {

    };

    struct DirectionalAudioComponent
    {

    };
}