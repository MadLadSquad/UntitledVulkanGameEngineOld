#include "Actor.hpp"
#include "Engine/GameFramework/Components/Components.hpp"
#include <GameFramework/Components/Components/CoreComponent.hpp>

UVK::Actor::Actor(const std::string& nameN, uint64_t idN, const std::string& devNameN) noexcept
{
    create(nameN, idN, devNameN);
}

entt::entity& UVK::Actor::data() noexcept
{
    return entity;
}

void UVK::Actor::create(const std::string& nameN, uint64_t idN, const std::string& devNameN) noexcept
{
    entity = global.ecs.data().create();
    auto& a = add<CoreComponent>();

    a.name = nameN;
    a.id = idN;
    a.uuid.generate();
    a.bHasUUID = true;
    a.devName = devNameN;
}

void UVK::Actor::destroy() noexcept
{
    clear();
    global.ecs.data().destroy(entity);
}

UVK::Actor::Actor(entt::entity ent) noexcept
{
    entity = ent;
}

bool UVK::Actor::operator==(entt::entity ent) noexcept
{
    return this->entity == ent;
}

bool UVK::Actor::operator==(UVK::Actor actor) noexcept
{
    return this->entity == actor.entity;
}

bool UVK::Actor::operator==(bool) noexcept
{
    return valid();
}

bool UVK::Actor::valid() noexcept
{
    return global.ecs.data().valid(entity);
}

UVK::Actor::operator bool() noexcept
{
    return valid();
}

void UVK::Actor::clear() noexcept
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

void UVK::Actor::createInternal(const std::string& nameN, uint64_t idN, const std::string& devNameN, bool bUsingUUID) noexcept
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