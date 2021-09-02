// ActorManager.cpp
// Last update 2/9/2021 by Madman10K
#include "ActorManager.hpp"
#include "Generated/ActorList.hpp"

void UVK::ActorManager::init()
{
    ACTOR_SET_DEPLOY

    for (auto& b : a)
    {
        if (b->id == 330 && b->name.find("Editor") == std::string::npos)
        {
            b->id = 331;
        }
    }
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
