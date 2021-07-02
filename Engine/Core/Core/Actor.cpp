// Actor.cpp
// Last update 30/6/2021 by Madman10K
#include <GL/glew.h>
#include "Actor.hpp"
#include <GameFramework/Actors/ActorManager.hpp>
#include <Core/Events/Events.hpp>
#include "Engine/GameFramework/Components/Components.hpp"

/*
void UVK::Registry::createActor(String name)
{
    Actor act = pool.create();

    auto& a = addComponent<UVK::CoreComponent>(act);
    a.name = name;

    // IDs should be used by the user for special scriptable objects
    a.id = 0;
}

void UVK::Registry::destroyActor(Actor &act)
{
    if (UVK::global.registry.hasComponent<UVK::MeshComponentRaw>(act))
    {
        auto& a = UVK::global.registry.getComponent<UVK::MeshComponentRaw>(act);

        a.clearMesh();

        pool.remove<UVK::MeshComponentRaw>(act);
    }

    for (auto& a : actorManager.data())
    {
        auto& b = UVK::global.registry.getComponent<UVK::CoreComponent>(act);

        if (a->name == b.name && a->devname == b.devName && a->id == b.id)
        {
            a->endPlay();
            actorManager.data().erase(a);
            break;
        }
    }

    pool.destroy(act);
}*/
UVK::Actor::Actor(const std::string& nameN, uint64_t idN, const std::string& devNameN, bool bCreatedByLevel)
{
    create(nameN, idN, devNameN, bCreatedByLevel);
}

entt::entity& UVK::Actor::data()
{
    return entity;
}

void UVK::Actor::create(const std::string& nameN, uint64_t idN, const std::string& devNameN, bool bCreatedByLevel)
{
    entity = global.ecs.data().create();

    auto& a = add<CoreComponent>();
    a.name = nameN;
    a.id = idN;
    a.devName = devNameN;

    for (auto& b : global.actorManager.data())
    {
        if (b->name == nameN && b->id == idN && b->devname == devNameN)
        {
            b->entities.push_back(this);
            global.events.add(b);
        }
    }
}

void UVK::Actor::destroy()
{
    const auto& component = get<CoreComponent>();

    std::vector<ScriptableObject*> temp;
    bool tested = false;
    for (auto& a : global.events.data())
    {
        if (a->id == component.id && a->name == component.name && a->devname == component.devName && !tested)
        {
            a->endPlay();

            tested = true;
        }
        else
        {
            temp.push_back(a);
        }
    }

    global.events.clear();
    global.events.data() = std::move(temp);

    global.ecs.data().destroy(entity);
}
