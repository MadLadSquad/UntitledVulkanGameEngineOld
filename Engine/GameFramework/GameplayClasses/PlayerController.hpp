// PlayerController.hpp
// Last update 2/24/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../Actors/APawn.hpp"

namespace UVK
{
    UVK_API class PlayerController
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

        APawn* currentPawn;
    private:

    };
}
