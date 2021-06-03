// PlayerController.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../Actors/APawn.hpp"

namespace UVK
{
    /**
     * @brief A player controller is the so called "soul" of the player. It can possess pawns as well as have
     * the standard events
     */
    class PlayerController
    {
    public:
        PlayerController() = default;

        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;
        void possess(APawn* pawn)
        {
            currentPawn = pawn;
        }

        APawn* currentPawn{};

        virtual ~PlayerController()
        {
            delete currentPawn;
        }
    private:

    };
}
