// ECSInterface.cpp
// Last update 22/9/2021 by Madman10K
#include "ECSInterface.hpp"
#include <Core/Global.hpp>
#include <GameFramework/Components/Components.hpp>
#include <Core/Actor.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>

void UVK::ECS::clear()
{
    global.ecs.clear();
}

UVK::EntityPool& UVK::ECS::data()
{
    return global.ecs.data();
}

void UVK::ECS::each(const std::function<void(Actor&)>& func)
{
    auto view = global.ecs.data().view<CoreComponent>();
    for (auto& a : view)
    {
        Actor act(a);
        func(act);
    }
}

void UVK::ECS::call(const std::function<void(Actor&)>& func, entt::entity& ent)
{
    Actor act(ent);

    func(act);
}

UVK::Actor UVK::ECS::getActorWithIdentifiers(const std::string& name, const uint64_t& id, const std::string& devname)
{
    auto view = global.ecs.data().view<CoreComponent>();
    for (auto& a : view)
    {
        Actor act(a);

        const auto& comp = act.get<CoreComponent>();
        if (comp.name == name && comp.id == id && comp.devName == devname)
            return act;
    }

    entt::entity a;
    return Actor(a);
}
