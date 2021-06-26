// Renderer.cpp
// Last update 26/6/2021 by Madman10K
#include "Registry.hpp"
#include <GameFramework/Actors/ActorManager.hpp>

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
    if (registry.hasComponent<UVK::MeshComponentRaw>(act))
    {
        auto& a = registry.getComponent<UVK::MeshComponentRaw>(act);

        a.clearMesh();

        pool.remove<UVK::MeshComponentRaw>(act);
    }

    for (auto& a : actorManager.data())
    {
        auto& b = registry.getComponent<UVK::CoreComponent>(act);

        if (a->name == b.name && a->devname == b.devName && a->id == b.id)
        {
            a->endPlay();
            actorManager.data().erase(a);
            break;
        }
    }

    pool.destroy(act);
}