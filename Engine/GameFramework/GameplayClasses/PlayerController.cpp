#include "PlayerController.hpp"

void UVK::PlayerController::possess(UVK::Pawn* pw) noexcept
{
    Pawn::destroyPawn(pawn);
    pawn = pw;
    pawn->beginPlay();
}

UVK::PlayerController::~PlayerController() noexcept
{
    delete pawn;
}

void UVK::PlayerController::destroyPlayerController(PlayerController* pc) noexcept
{
    pc->endPlay();
    delete pc;
}

void UVK::PlayerController::beginAutohandle() const noexcept
{
    pawn->beginPlay();
}

void UVK::PlayerController::tickAutohandle(float deltaTime) const noexcept
{
    pawn->tick(deltaTime);
}

void UVK::PlayerController::endAutohandle() const noexcept
{
    pawn->endPlay();
}
