// EditorPlayerController.cpp
// Last update 27/8/2021 by Madman10K
#include "EditorPlayerController.hpp"
#ifndef PRODUCTION
#include "EditorPawn.hpp"

UVK::EditorPlayerController::EditorPlayerController()
{
    pawn = Pawn::makePawn<EditorPawn>();
}

void UVK::EditorPlayerController::beginPlay()
{
    if (!global.getEditor())
        logger.consoleLog("You are currently using an Editor Player Controller ingame. This is a safety measure in order to prevent instant crashes of your game, however, the code for the EditorPlayerController will not compile in production which will cause a crash!", UVK_LOG_TYPE_ERROR);
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
#endif