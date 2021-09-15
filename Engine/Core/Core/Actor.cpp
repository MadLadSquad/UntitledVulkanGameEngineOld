// Actor.cpp
// Last update 15/9/2021 by Madman10K
#include <GL/glew.h>
#include "Actor.hpp"
#include <GameFramework/Actors/ActorManager.hpp>
#include "Engine/GameFramework/Components/Components.hpp"

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
    a.name = nameN;
    a.id = idN;
    a.devName = devNameN;
}

void UVK::Actor::destroy()
{
    if (global.ecs.data().any_of<AudioComponent>(entity))
    {
        global.ecs.data().get<AudioComponent>(entity).stop();
    }

    if (global.ecs.data().any_of<MeshComponentRaw>(entity))
    {
        global.ecs.data().get<MeshComponentRaw>(entity).clearMesh();
    }

    if (global.ecs.data().any_of<MeshComponent>(entity))
    {
        global.ecs.data().get<MeshComponent>(entity).clearMesh();
    }

    global.ecs.data().destroy(entity);
}

UVK::Actor::Actor(entt::entity ent)
{
    entity = ent;
}