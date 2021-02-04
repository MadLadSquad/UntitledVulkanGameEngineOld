// GameMode.hpp
// Last update 1/10/2021 by Madman10K
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
        GameMode() = delete;

        GameMode(GameState* gs, PlayerState* ps, PlayerController* pc, APawn* pawn)
        {
            this->gs = gs;
            this->ps = ps;
            this->pc = pc;
            this->pawn = pawn;
        }

        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        void setGameState(GameState* gameState){ gs = gameState; }
        void setPlayerState(PlayerState* playerState){ ps = playerState; }
        void setPlayerController(PlayerController* playerController){ pc = playerController; }
        void setPawn(APawn* pawn) { this->pawn = pawn; }

        GameState& setGameState(){ return *gs; }
        PlayerState& getPlayerState() { return *ps; }
        PlayerController& getPlayerController() { return *pc; }
        APawn& getPawn() { return *pawn; }

    private:
        GameState* gs;
        PlayerState* ps;
        PlayerController* pc;
        APawn* pawn;
    };
}
