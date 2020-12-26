// Components.hpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include <Core.hpp>

namespace UVK
{
    UVK_API struct CoreComponent
    {
        String name;
    };

    struct TransformComponent
    {
        glm::mat4 Translate(glm::mat4* model, FVector translation)
        {
            return glm::translate(*model, translation);
        }

        glm::mat4 Rotate(glm::mat4* model, float degrees, FVector rotation)
        {
            return glm::rotate(*model, glm::radians(degrees), rotation);
        }

        glm::mat4 Scale(glm::mat4* model, FVector scale)
        {
            return glm::scale(*model, scale);
        }
    };

    UVK_API struct MeshComponent
    {

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
}