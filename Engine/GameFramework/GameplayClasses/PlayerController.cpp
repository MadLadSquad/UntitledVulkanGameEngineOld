// PlayerController.cpp
// Last update 22/9/2021 by Madman10K
#include "PlayerController.hpp"

void UVK::PlayerController::possess(UVK::Pawn* pw)
{
    Pawn::destroyPawn(pawn);
    pawn = pw;
    pawn->beginPlay();
}

UVK::PlayerController::~PlayerController()
{
    delete pawn;
}

void UVK::PlayerController::destroyPlayerController(PlayerController* pc)
{
    pc->endPlay();
    delete pc;
}

void UVK::PlayerController::beginAutohandle() const
{
    pawn->beginPlay();
}

void UVK::PlayerController::tickAutohandle(float deltaTime) const
{
    pawn->tick(deltaTime);
}

void UVK::PlayerController::endAutohandle() const
{
    pawn->endPlay();
}
