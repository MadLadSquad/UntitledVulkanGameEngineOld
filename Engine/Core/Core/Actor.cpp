// Actor.cpp
// Last update 28/9/2021 by Madman10K
#include <GL/glew.h>
#include "Actor.hpp"
#include "Engine/GameFramework/Components/Components.hpp"
#include <GameFramework/Components/Components/CoreComponent.hpp>

UVK::Actor::Actor(const std::string& nameN, uint64_t idN, const std::string& devNameN)
{
    create(nameN, idN, devNameN);
}

entt::entity& UVK::Actor::data()
{
    return entity;
}

void UVK::Actor::create(const std::string& nameN, uint64_t idN, const std::string& devNameN)
{
    entity = global.ecs.data().create();
    auto& a = add<CoreComponent>();

    if (idN == 330 && nameN.find("Editor") == std::string::npos)
        idN = 331;

    a.name = nameN;
    a.id = idN;
    a.devName = devNameN;
}

void UVK::Actor::destroy()
{
    if (has<MeshComponentRaw>())
    {
        get<MeshComponentRaw>().clearMesh();
        remove<MeshComponentRaw>();
    }

    if (has<MeshComponent>())
    {
        get<MeshComponent>().clearMesh();
        remove<MeshComponent>();
    }
    remove<CoreComponent>();

    global.ecs.data().destroy(entity);
}

UVK::Actor::Actor(entt::entity ent)
{
    entity = ent;
}