// PlayerController.hpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include <Core.hpp>
#include "../Actors/APawn.hpp"

namespace UVK
{
    UVK_API class PlayerController
    {
    public:
        virtual void BeginPlay() = 0;
        virtual void Tick(float DeltaTime) = 0;
        virtual void EndPlay() = 0;
        void Possess(APawn* pawn)
        {
            currentPawn = pawn;
        }

        void SetStarterPawn(APawn* pawn)
        {
            currentPawn = pawn;
        }
    private:
        APawn* currentPawn;
    };
}