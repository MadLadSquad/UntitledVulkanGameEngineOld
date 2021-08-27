// GameMode.cpp
// Last update 27/8/2021 by Madman10K
#include "GameMode.hpp"

UVK::GameMode::~GameMode()
{
    delete gameState;
    delete playerState;
    delete playerController;
}

void UVK::GameMode::beginAutohandle() const
{
    gameState->beginPlay();
    playerState->beginPlay();
    playerController->beginPlay();
}

void UVK::GameMode::tickAutohandle(float deltaTime) const
{
    gameState->tick(deltaTime);
    playerState->tick(deltaTime);
    playerController->tick(deltaTime);
}

void UVK::GameMode::endAutohandle() const
{
    gameState->endPlay();
    playerState->endPlay();
    playerController->endPlay();
}

void UVK::GameMode::destroyGameMode(GameMode* gm)
{
    gm->endPlay();
    delete gm;
}

UVK::Pawn* UVK::GameMode::getPawn(UVK::GameMode* gm)
{
    return gm->playerController->pawn;
}
