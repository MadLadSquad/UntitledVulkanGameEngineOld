// GameMode.cpp
// Last update 19/7/2021 by Madman10K
#include "GameMode.hpp"

UVK::GameMode::~GameMode()
{
    if (gs != nullptr)
    {
        delete gs;
    }

    if (ps != nullptr)
    {
        delete ps;
    }

    if (pc != nullptr)
    {
        delete pc;
    }

    if (pawn != nullptr)
    {
        delete pawn;
    }
}

void UVK::GameMode::beginAutohandle() const
{
    gs->beginPlay();
    ps->beginPlay();
    pc->beginPlay();
    pawn->beginPlay();
}

void UVK::GameMode::tickAutohandle(float deltaTime) const
{
    gs->tick(deltaTime);
    ps->tick(deltaTime);
    pc->tick(deltaTime);
    pawn->tick(deltaTime);
}

void UVK::GameMode::endAutohandle() const
{
    gs->endPlay();
    ps->endPlay();
    pc->endPlay();
    pawn->endPlay();
}

void UVK::destroyGameMode(GameMode* gm)
{
    gm->endPlay();
    delete gm;
}