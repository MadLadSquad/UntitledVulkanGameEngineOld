#include "ActorManager.hpp"
#include "Generated/ActorList.hpp"

void UVK::ActorManager::init() noexcept
{
    a.clear();
    ACTOR_SET_DEPLOY
}

void UVK::ActorManager::destroy() noexcept
{
    for (auto* b : a)
        delete b;
}

std::vector<UVK::ScriptableObject*>& UVK::ActorManager::data() noexcept
{
    return a;
}

UVK::ActorManager::~ActorManager() noexcept
{
    destroy();
    a.clear();
}