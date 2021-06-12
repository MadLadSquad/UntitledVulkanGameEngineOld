// Events.cpp
// Last update 9/6/2021 by Madman10K
#include "Events.hpp"

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