#include "EditorLevel.hpp"
#ifndef PRODUCTION
void UVK::EditorLevel::beginPlay()
{
    if (!global.getEditor())
        Logger::log("You are currently using an Editor Game Level ingame. This is a safety measure in order to prevent instant crashes of your game, however, the code for the EditorLevel will not compile in production which will cause a crash!", UVK_LOG_TYPE_ERROR);

    beginAutohandle();
}

void UVK::EditorLevel::tick(float deltaTime)
{
	tickAutohandle(deltaTime);
}

void UVK::EditorLevel::endPlay()
{
	endAutohandle();
}
#endif