// GameMode.cpp
// Last update 19/7/2021 by Madman10K
#include "GameMode.hpp"

UVK::GameMode::~GameMode()
{
    delete gs;
    delete ps;
    delete pc;
    delete pawn;
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