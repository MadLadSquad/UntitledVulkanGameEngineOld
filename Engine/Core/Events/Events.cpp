// Events.cpp
// Last update 13/9/2021 by Madman10K
#include "Events.hpp"
#include <GameFramework/Actors/ScriptableObject.hpp>
#include <Core/Global.hpp>

void UVK::Events::clear()
{
    global.instance->actorManager.destroy();
    global.instance->actorManager.init();
}

void UVK::Events::callTick(float deltaTime)
{
    for (auto& a : global.instance->actorManager.data())
    {
        switch (a->activityFlags)
        {
        case SCRIPTABLE_OBJECT_ACTIVITY_FLAG_DISABLED:
            break;
        case SCRIPTABLE_OBJECT_ACTIVITY_FLAG_ACTIVE:
            a->tick(deltaTime);
            break;
        case SCRIPTABLE_OBJECT_ACTIVITY_FLAG_INACTIVE:
            a->inactiveTick(deltaTime);
            break;
        }
    }
}

void UVK::Events::callBegin()
{
    for (auto& a : global.instance->actorManager.data())
    {
        switch (a->activityFlags)
        {
        case SCRIPTABLE_OBJECT_ACTIVITY_FLAG_DISABLED:
            break;
        case SCRIPTABLE_OBJECT_ACTIVITY_FLAG_ACTIVE:
            a->beginPlay();
            break;
        case SCRIPTABLE_OBJECT_ACTIVITY_FLAG_INACTIVE:
            a->inactiveBegin();
            break;
        }
    }
}

void UVK::Events::callEnd()
{
    for (auto& a : global.instance->actorManager.data())
    {
        switch (a->activityFlags)
        {
        case SCRIPTABLE_OBJECT_ACTIVITY_FLAG_DISABLED:
            break;
        case SCRIPTABLE_OBJECT_ACTIVITY_FLAG_ACTIVE:
            a->endPlay();
            break;
        case SCRIPTABLE_OBJECT_ACTIVITY_FLAG_INACTIVE:
            a->inactiveEnd();
            break;
        }
    }
}