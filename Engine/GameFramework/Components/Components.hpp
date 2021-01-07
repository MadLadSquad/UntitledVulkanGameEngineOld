// Components.hpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)
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