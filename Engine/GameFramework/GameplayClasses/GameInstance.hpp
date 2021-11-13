// GameInstance.hpp
// Last update 22/9/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <GameFramework/Actors/ActorManager.hpp>
#include <Events/Events.hpp>
#include <Core/State/StateTracker.hpp>

namespace UVK
{
    class Editor;
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
        static Level* currentLevel();

        template<typename T>
        static T* cast(GameInstance* gi)
        {
            return static_cast<T*>(gi);
        }

        virtual ~GameInstance() = default;
    private:
        friend class Actor;
        friend class Level;
        friend class GLPipeline;
        friend class Events;
        friend class Editor;
        friend class EditorModules;
        friend class EditorPawn;
        friend class StateTracker;
        friend class Renderer;
        friend class Utility;
        friend struct EditorPointer;
        friend struct RendererSettings;

        Editor* editor = nullptr;
        UVK::ActorManager actorManager;
        UVK::StateTracker stateTracker;
    };
}