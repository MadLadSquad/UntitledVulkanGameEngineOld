// GameState.hpp
// Last update 7/2/2022 by Madman10K
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
        static GameState* makeGameState()
        {
            T* gs = new T();
            return gs;
        }

        template<typename T>
        static T* cast(GameState* gs)
        {
            return static_cast<T*>(gs);
        }

        static void destroyGameState(GameState* gs);
    };
}