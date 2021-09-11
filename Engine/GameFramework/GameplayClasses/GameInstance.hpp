// GameInstance.hpp
// Last update 27/8/2021 by Madman10K
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
        virtual void onEventInitEditorModules() = 0; // Add any editor module declaration here

        // Shutdown your game
        static void exit();

        template<typename T>
        static T* cast(GameInstance* gi)
        {
            return static_cast<T*>(gi);
        }

        virtual ~GameInstance();
    private:
        friend class Actor;
        friend class Level;
        friend class GLPipeline;

        UVK::ActorManager actorManager;
        UVK::Events events;
    };
}