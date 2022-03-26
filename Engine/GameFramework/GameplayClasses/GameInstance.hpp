#pragma once
#include <GameFramework/Actors/ActorManager.hpp>
#include <Core/State/StateTracker.hpp>

namespace UVK
{
    class Editor;
    /**
     * @brief The instance of the application
     */
    class UVK_PUBLIC_API GameInstance
    {
    public:
        GameInstance() noexcept;

        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;
        virtual void onEventInitEditorModules() = 0; // Add any editor module declaration here

        // Shutdown your game
        static void exit() noexcept;
        static Level* currentLevel() noexcept;

        template<typename T>
        static T* cast(GameInstance* gi) noexcept
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
        friend class EditorResources;
        friend class EditorGUIUtils;
        friend struct EditorPointer;
        friend struct RendererSettings;

        Editor* editor = nullptr;
        UVK::ActorManager actorManager;
        UVK::StateTracker stateTracker;
    };
}