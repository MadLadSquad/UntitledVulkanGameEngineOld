// Actor.cpp
// Last update 13/10/2021 by Madman10K
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

    a.name = nameN;
    a.id = idN;
    a.uuid.generate();
    a.bHasUUID = true;
    a.devName = devNameN;
}

void UVK::Actor::destroy()
{
    clear();
    global.ecs.data().destroy(entity);
}

UVK::Actor::Actor(entt::entity ent)
{
    entity = ent;
}

bool UVK::Actor::operator==(entt::entity ent)
{
    return this->entity == ent;
}

bool UVK::Actor::operator==(UVK::Actor actor)
{
    return this->entity == actor.entity;
}

bool UVK::Actor::operator==(bool)
{
    return valid();
}

bool UVK::Actor::valid()
{
    return global.ecs.data().valid(entity);
}

UVK::Actor::operator bool()
{
    return valid();
}

void UVK::Actor::clear()
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

    if (has<AudioComponent>())
    {
        auto& audio = get<AudioComponent>();
        audio.stop();
        remove<AudioComponent>();
    }

    if (has<CoreComponent>())
        remove<CoreComponent>();
}

void UVK::Actor::createInternal(const std::string& nameN, uint64_t idN, const std::string& devNameN, bool bUsingUUID)
{
    entity = global.ecs.data().create();
    auto& a = add<CoreComponent>();

    a.name = nameN;
    a.id = idN;
    if (bUsingUUID)
    {
        a.uuid.generate();
        a.bHasUUID = true;
    }
    else
    {
        a.uuid.id = 330;
        a.bHasUUID = false;
    }

    a.devName = devNameN;
}