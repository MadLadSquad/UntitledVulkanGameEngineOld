// GameMode.hpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include <Core.hpp>
#include "GameState.hpp"
#include "PlayerState.hpp"
#include "PlayerController.hpp"
#include "../Actors/APawn.hpp"

namespace UVK
{
    UVK_API class GameMode
    {
    public:
        virtual void BeginPlay() = 0;
        virtual void Tick(float DeltaTime) = 0;
        virtual void EndPlay() = 0;

        void SetGameState(GameState* gameState){ gs = gameState; }
        void SetPlayerState(PlayerState* playerState){ ps = playerState; }
        void SetPlayerController(PlayerController* playerController){ pc = playerController; }
        void SetPawn(APawn* pawn) { this->pawn = pawn; }

        GameState& GetGameState(){ return *gs; }
        PlayerState& GetPlayerState() { return *ps; }
        PlayerController& GetPlayerController() { return *pc; }
        APawn& GetPawn() { return *pawn; }

    private:
        GameState* gs;
        PlayerState* ps;
        PlayerController* pc;
        APawn* pawn;
    };
}
