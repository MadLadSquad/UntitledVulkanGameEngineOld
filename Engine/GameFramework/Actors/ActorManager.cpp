// ActorManager.cpp
// Last update 5/6/2021 by Madman10K
#include <GL/glew.h>
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
