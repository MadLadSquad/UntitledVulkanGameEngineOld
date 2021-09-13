// ActorManager.cpp
// Last update 13/9/2021 by Madman10K
#include "ActorManager.hpp"
#include "Generated/ActorList.hpp"

void UVK::ActorManager::init()
{
    ACTOR_SET_DEPLOY
}

void UVK::ActorManager::destroy()
{
    for (auto& b : a)
    {
        delete b;
    }
}

std::set<UVK::ScriptableObject*>& UVK::ActorManager::data()
{
    return a;
}

UVK::ActorManager::~ActorManager()
{
    destroy();
    a.clear();
}