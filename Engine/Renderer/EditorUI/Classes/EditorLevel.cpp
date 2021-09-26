// EditorLevel.cpp
// Last update 27/8/2021 by Madman10K
#include "EditorLevel.hpp"
#ifndef PRODUCTION
void UVK::EditorLevel::beginPlay()
{
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