// EditorPlayerController.cpp
// Last update 27/8/2021 by Madman10K
#include "EditorPlayerController.hpp"
#include "EditorPawn.hpp"

UVK::EditorPlayerController::EditorPlayerController()
{
    pawn = Pawn::makePawn<EditorPawn>();
}

void UVK::EditorPlayerController::beginPlay()
{
    beginAutohandle();
}

void UVK::EditorPlayerController::tick(float deltaTime)
{
    tickAutohandle(deltaTime);
}

void UVK::EditorPlayerController::endPlay()
{
    endAutohandle();
}