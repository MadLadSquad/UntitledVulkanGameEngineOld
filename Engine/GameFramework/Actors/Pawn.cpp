// Pawn.cpp
// Last update 22/9/2021 by Madman10K
#include "Pawn.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include "FallbackPawn.hpp"

void UVK::Pawn::destroyPawn(Pawn* pw)
{
    bool bUsingFallbackPawn = false;
    if (global.currentLevel->gameMode->playerController->pawn == pw)
        bUsingFallbackPawn = true;

    pw->endPlay();
    delete pw;

    if (bUsingFallbackPawn)
    {
        logger.consoleLog("You are trying to destroy the pawn you are currently using! Switching to fallback pawn!", UVK_LOG_TYPE_ERROR);

        auto* fbp = new FallbackPawn();
        global.currentLevel->gameMode->playerController->pawn = fbp;
    }
}

UVK::Pawn::~Pawn()
{
    actor.destroy();
}