// Components.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <GL/glew.h>

#include <../Renderer/OpenGL/Components/GLMesh.hpp>
#include <../Renderer/OpenGL/Components/GLCamera.hpp>
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
     * @param name - the name of the entity
     * @param id - user defined integer for id
     * @param devName - to sort by name when developing
     */
    struct CoreComponent
    {
        std::string name;
        uint64_t id;
        std::string devName;
    private:
        // In order for the program to not crash when there is no data in id or name
        static constexpr char a = 'a';
    };
}