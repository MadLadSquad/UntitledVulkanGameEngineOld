// PlayerController.hpp
// Last update 1/10/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../Actors/APawn.hpp"

namespace UVK
{
    UVK_API class PlayerController
    {
    public:
        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;
        void possess(APawn* pawn)
        {
            currentPawn = pawn;
        }

        void setStarterPawn(APawn* pawn)
        {
            currentPawn = pawn;
        }
    private:
        APawn* currentPawn;
    };
}