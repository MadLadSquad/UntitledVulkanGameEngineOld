// GameState.hpp
// Last update 3/6/2021 by Madman10K
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
}