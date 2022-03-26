#include "GameMode.hpp"

UVK::GameMode::~GameMode() noexcept
{
    delete gameState;
    delete playerState;
    delete playerController;
}

void UVK::GameMode::beginAutohandle() const noexcept
{
    gameState->beginPlay();
    playerState->beginPlay();
    playerController->beginPlay();
}

void UVK::GameMode::tickAutohandle(float deltaTime) const noexcept
{
    gameState->tick(deltaTime);
    playerState->tick(deltaTime);
    playerController->tick(deltaTime);
}

void UVK::GameMode::endAutohandle() const noexcept
{
    gameState->endPlay();
    playerState->endPlay();
    playerController->endPlay();
}

void UVK::GameMode::destroyGameMode(GameMode* gm) noexcept
{
    gm->endPlay();
    delete gm;
}

UVK::Pawn* UVK::GameMode::getPawn(UVK::GameMode* gm) noexcept
{
    return gm->playerController->pawn;
}
