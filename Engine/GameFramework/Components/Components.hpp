// Components.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <Audio/Audio.hpp>
#include "Components/MeshComponentRaw.hpp"
#include "Components/MeshComponent.hpp"
#include "Components/AudioComponent.hpp"

namespace UVK
{
    /**
     * @brief A mesh component flag states they given object's light rendering properties (Not yet implemented)
     * @param MESH_FLAG_STATIC - A static object that never moves, always receives baked lighting
     * @param MESH_FLAG_STATIONARY - A stationary object is rendered with baked lighting and moves to dynamic lighting after movement
     * @param MESH_FLAG_DYNAMIC - A dynamic object that always moves which makes it always render with dynamic lighting
     */
    enum MeshComponentFlags
    {
        MESH_FLAG_STATIC,
        MESH_FLAG_STATIONARY,
        MESH_FLAG_DYNAMIC
    };

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