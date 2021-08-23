// PlayerController.cpp
// Last update 2/7/2021 by Madman10K
#include <GL/glew.h>
#include "PlayerController.hpp"

void UVK::PlayerController::possess(UVK::APawn* pawn)
{
    currentPawn = pawn;
}

UVK::PlayerController::~PlayerController()
{
    delete currentPawn;
}

void UVK::PlayerController::destroyPlayerController(PlayerController* pc)
{
    pc->endPlay();
    delete pc;
}