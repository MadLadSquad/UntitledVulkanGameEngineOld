// Events.cpp
// Last update 27/8/2021 by Madman10K
#include "Events.hpp"
#include <GameFramework/Actors/ScriptableObject.hpp>

void UVK::Events::add(ScriptableObject* sco)
{
    objList.push_back(sco);
}

void UVK::Events::clear()
{
    objList.clear();
}

void UVK::Events::callTick(float deltaTime)
{
    for (auto& a : objList)
    {
        a->tick(deltaTime);
    }
}

void UVK::Events::callBegin()
{
    for (auto& a : objList)
    {
        a->beginPlay();
    }
}

void UVK::Events::callEnd()
{
    for (auto& a : objList)
    {
        a->endPlay();
    }
}

std::vector<UVK::ScriptableObject*>& UVK::Events::data()
{
    return objList;
}
