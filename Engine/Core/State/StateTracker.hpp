// StateTracker.hpp
// Last update 22/9/2021 by Madman10K
#pragma once
#include <vector>
#include <cstdint>

namespace UVK
{
    class Actor;

    enum ActorActions
    {
        ACTOR_ACTION_MOVE,
        ACTOR_ACTION_SCALE,
        ACTOR_ACTION_ROTATE,

        ACTOR_ACTION_CREATE,
        ACTOR_ACTION_DESTROY, // TODO: recreating actors and components will be implemented later
        ACTOR_ACTION_ADD_COMPONENT, // TODO: recreating actors and components will be implemented later
        ACTOR_ACTION_REMOVE_COMPONENT // TODO: recreating actors and components will be implemented later
    };

    /**
     * @brief Tracks state changes for the editor and actors. Handles things like Undo/Redo, stores states
     * of components and much more
     */
    class StateTracker
    {
    public:
        StateTracker() = default;

        // Saves an actor action to the actor action undo/redo
        void addActorAction(ActorActions action, Actor& actor);
        void undoActorAction();
        void redoActorAction();
    private:
        std::pair<ActorActions, Actor*> actorActions[50];
        uint8_t actorActionIndex = 0;
    };
}
