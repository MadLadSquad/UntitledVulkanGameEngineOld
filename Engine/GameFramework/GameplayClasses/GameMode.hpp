// GameMode.hpp
// Last update 18/5/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "GameState.hpp"
#include "PlayerState.hpp"
#include "PlayerController.hpp"
#include "../Actors/APawn.hpp"

namespace UVK
{
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
    private:

    };
}
