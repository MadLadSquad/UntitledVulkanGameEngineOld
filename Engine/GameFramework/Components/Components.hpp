// Components.hpp
// Last update 2/9/2021 by Madman10K
#pragma once
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <Audio/Audio.hpp>
#include "Components/MeshComponentRaw.hpp"
#include "Components/MeshComponent.hpp"
#include "Components/AudioComponent.hpp"

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
    };
}