#include "Pawn.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include "FallbackPawn.hpp"

void UVK::Pawn::destroyPawn(Pawn* pw) noexcept
{
    bool bUsingFallbackPawn = false;
    if (global.currentLevel->gameMode->playerController->pawn == pw)
        bUsingFallbackPawn = true;

    pw->endPlay();
    delete pw;

    if (bUsingFallbackPawn)
    {
        Logger::log("You are trying to destroy the pawn you are currently using! Switching to fallback pawn!", UVK_LOG_TYPE_ERROR);

        auto* fbp = new FallbackPawn();
        global.currentLevel->gameMode->playerController->pawn = fbp;
    }
}

UVK::Pawn::~Pawn() noexcept
{
    actor.destroy();
}