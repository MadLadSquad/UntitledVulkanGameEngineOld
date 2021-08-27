// EditorGameMode.cpp
// Last update 27/8/2021 by Madman10K
#include "EditorGameMode.hpp"
#include "EditorPlayerController.hpp"

#ifndef PRODUCTION
void UVK::EditorGameMode::beginPlay()
{
    playerController->beginPlay();
}

void UVK::EditorGameMode::tick(float deltaTime)
{
    playerController->tick(deltaTime);
}

void UVK::EditorGameMode::endPlay()
{
    playerController->endPlay();
}

UVK::EditorGameMode::EditorGameMode()
{
    playerController = PlayerController::makePlayerController<EditorPlayerController>();
}
#endif