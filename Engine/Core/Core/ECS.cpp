#include "ECS.hpp"
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <Core/Actor.hpp>

void UVK::ECSManager::clear() noexcept
{
    pool.each([&](entt::entity ent) 
    {
        if (pool.any_of<CoreComponent>(ent))
        {
            UVK::Actor act(ent);
            act.destroy();
        }
    });
    pool.clear(); // TODO: Keep a close eye on this line
}

UVK::EntityPool& UVK::ECSManager::data() noexcept
{
    return pool;
}