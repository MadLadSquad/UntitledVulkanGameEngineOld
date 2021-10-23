// CoreComponent.hpp
// Last update 22/9/2021 by Madman10K
#pragma once
#include <iostream>
#include <Core/Types.hpp>

namespace UVK
{
    /**
     * @brief The base component every entity has
     * @param name, id, devName - used for identification of entities
     */
    struct CoreComponent
    {
        std::string name;
        uint64_t id;
        std::string devName;

        FVector translation = { 0.0f, 0.0f, 0.0f };
        FVector rotation = { 0.0f, 0.0f, 0.0f };
        FVector scale = { 1.0f, 1.0f, 1.0f };
    };
}