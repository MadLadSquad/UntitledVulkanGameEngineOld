// EditorGameMode.cpp
// Last update 27/8/2021 by Madman10K
#include "EditorGameMode.hpp"
#include "EditorPlayerController.hpp"

#ifndef PRODUCTION
void UVK::EditorGameMode::beginPlay()
{
    if (!global.getEditor())
        logger.consoleLog("You are currently using an Editor Game Mode ingame. This is a safety measure in order to prevent instant crashes of your game, however, the code for the EditorGameMode will not compile in production which will cause a crash!", UVK_LOG_TYPE_ERROR);

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