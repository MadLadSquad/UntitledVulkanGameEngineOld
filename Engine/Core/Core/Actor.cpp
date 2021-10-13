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

    if (idN == 330 && nameN.find("Editor") == std::string::npos)
        idN = 331;

    a.name = nameN;
    a.id = idN;
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
    remove<CoreComponent>();
}
