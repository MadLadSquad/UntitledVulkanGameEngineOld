// GameState.hpp
// Last update 19/7/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    /**
     * @brief A game state is a simple class that semantically should be used to track the state of the game
     */
    class GameState
    {
    public:
        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        virtual ~GameState() = default;
    };

    template<typename T>
    static GameState* makeGameState()
    {
        T* gs = new T();
        return gs;
    }

    static void destroyGameState(GameState* gs);
}