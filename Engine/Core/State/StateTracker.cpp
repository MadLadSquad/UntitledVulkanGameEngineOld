// StateTracker.cpp
// Last update 22/9/2021 by Madman10K
#include "StateTracker.hpp"
#include <Core/Actor.hpp>

void UVK::StateTracker::addActorAction(UVK::ActorActions action, UVK::Actor& actor)
{
    if (actorActionIndex == 50)
    {
        actorActionIndex = 0;
    }

    actorActions[actorActionIndex].first = action;
    actorActions[actorActionIndex].second = &actor;

    actorActionIndex++;
}

void UVK::StateTracker::undoActorAction()
{
    auto& pair = actorActions[actorActionIndex - 1];

    switch (pair.first)
    {
    case ACTOR_ACTION_MOVE:
        break;
    case ACTOR_ACTION_SCALE:
        break;
    case ACTOR_ACTION_ROTATE:
        break;
    case ACTOR_ACTION_CREATE:
        break;
    case ACTOR_ACTION_DESTROY:
        break;
    case ACTOR_ACTION_ADD_COMPONENT:
        break;
    case ACTOR_ACTION_REMOVE_COMPONENT:
        break;
    }
}

void UVK::StateTracker::redoActorAction()
{
}
