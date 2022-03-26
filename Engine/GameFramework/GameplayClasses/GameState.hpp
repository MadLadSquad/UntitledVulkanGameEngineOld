#pragma once
#include <Core.hpp>

namespace UVK
{
    /**
     * @brief A game state is a simple class that semantically should be used to track the state of the game
     */
    class UVK_PUBLIC_API GameState
    {
    public:
        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        virtual ~GameState() = default;

        template<typename T>
        [[maybe_unused]] static GameState* makeGameState() noexcept
        {
            T* gs = new T();
            return gs;
        }

        template<typename T>
        static T* cast(GameState* gs) noexcept
        {
            return static_cast<T*>(gs);
        }

        [[maybe_unused]] static void destroyGameState(GameState* gs) noexcept;
    };
}