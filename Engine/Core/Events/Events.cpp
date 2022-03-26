#include "Events.hpp"
#include <GameFramework/Actors/ScriptableObject.hpp>
#include <Core/Global.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>

void UVK::Events::clear() noexcept
{
    global.instance->actorManager.destroy();
    global.instance->actorManager.init();
}

void UVK::Events::callTick(float deltaTime) noexcept
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
    global.modtick(deltaTime);
}

void UVK::Events::callBegin() noexcept
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
    global.modbegin();
}

void UVK::Events::callEnd() noexcept
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
    global.modend();
}