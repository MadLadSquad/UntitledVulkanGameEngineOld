// GameInstance.hpp
// Last update 21/7/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <GameFramework/Actors/ActorManager.hpp>
#include <Events/Events.hpp>

namespace UVK
{
    /**
     * @brief The instance of the application
     */
    class GameInstance
    {
    public:
        GameInstance();

        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;

        virtual ~GameInstance();
    private:
        friend class Actor;
        friend class Level;
        friend class GLPipeline;

        UVK::ActorManager actorManager;
        UVK::Events events;
    };
}