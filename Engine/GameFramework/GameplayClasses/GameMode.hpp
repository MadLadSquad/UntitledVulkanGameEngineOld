// GameMode.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "GameState.hpp"
#include "PlayerState.hpp"
#include "PlayerController.hpp"
#include "../Actors/APawn.hpp"

namespace UVK
{
    /**
     * @brief A game mode contains pointers to a GameState, PlayerState, PlayerController and a Pawn
     */
    class GameMode
    {
    public:
        GameMode() = default;

        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        GameState* gs = nullptr;
        PlayerState* ps = nullptr;
        PlayerController* pc = nullptr;
        APawn* pawn = nullptr;

        virtual ~GameMode()
        {
            delete gs;
            delete ps;
            delete pc;
            delete pawn;
        }

        void beginAutohandle() const
        {
            gs->beginPlay();
            ps->beginPlay();
            pc->beginPlay();
            pawn->beginPlay();
        }

        void tickAutohandle(float deltaTime) const
        {
            gs->tick(deltaTime);
            ps->tick(deltaTime);
            pc->tick(deltaTime);
            pawn->tick(deltaTime);
        }

        void endAutohandle() const
        {
            gs->endPlay();
            ps->endPlay();
            pc->endPlay();
            pawn->endPlay();
        }
    private:
    };
}
