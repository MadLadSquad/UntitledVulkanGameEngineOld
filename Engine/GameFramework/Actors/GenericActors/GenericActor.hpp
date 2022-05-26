#pragma once
#include <Core/Actor.hpp>

namespace UVK
{
    struct PointLightComponent;

    enum GenericObjectType
    {
        GENERIC_OBJECT_TYPE_CUBE,
        GENERIC_OBJECT_TYPE_SPHERE,
        GENERIC_OBJECT_TYPE_CYLINDER,
        GENERIC_OBJECT_TYPE_CONE,
        GENERIC_OBJECT_TYPE_PLANE,
        GENERIC_OBJECT_TYPE_PYRAMID,
        GENERIC_OBJECT_TYPE_TEAPOT,
        GENERIC_OBJECT_TYPE_MONKEY,
        GENERIC_OBJECT_TYPE_POINT_LIGHT,
        GENERIC_OBJECT_TYPE_DIRECTIONAL_LIGHT
    };

#define CREATE_MESH_CALL(x, y) \
    if constexpr (T == (x)) \
    { \
        createMesh(y); \
        return; \
    } \


    class GenericActor
    {
    public:
        template<GenericObjectType T>
        static void createGenericObject() noexcept
        {
            CREATE_MESH_CALL(GENERIC_OBJECT_TYPE_CUBE, "../Content/Engine/generic_object_cube.obj");
            CREATE_MESH_CALL(GENERIC_OBJECT_TYPE_SPHERE, "../Content/Engine/generic_object_sphere.obj");
            CREATE_MESH_CALL(GENERIC_OBJECT_TYPE_CYLINDER, "../Content/Engine/generic_object_cylinder.obj");
            CREATE_MESH_CALL(GENERIC_OBJECT_TYPE_CONE, "../Content/Engine/generic_object_cone.obj");
            CREATE_MESH_CALL(GENERIC_OBJECT_TYPE_PLANE, "../Content/Engine/generic_object_plane.obj");
            CREATE_MESH_CALL(GENERIC_OBJECT_TYPE_PYRAMID, "../Content/Engine/generic_object_pyramid.obj");
            CREATE_MESH_CALL(GENERIC_OBJECT_TYPE_TEAPOT, "../Content/Engine/generic_object_teapot.obj");
            CREATE_MESH_CALL(GENERIC_OBJECT_TYPE_MONKEY, "../Content/Engine/generic_object_monkey.obj");

            if constexpr (T == GENERIC_OBJECT_TYPE_POINT_LIGHT)
            {
                static size_t i = 0;
                Actor actor("GenericLightActor", i, "GenericLightActor" + std::to_string(i));
                actor.add<PointLightComponent>();
                i++;
                return;
            }

            if constexpr (T == GENERIC_OBJECT_TYPE_DIRECTIONAL_LIGHT)
            {

                return;
            }
        }
    private:
        static void createMesh(const FString& path) noexcept;
    };
}