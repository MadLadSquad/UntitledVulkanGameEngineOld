// GameState.cpp
// Last update 19/7/2021 by Madman10K
#include <GL/glew.h>
#include "GameState.hpp"

void UVK::GameState::destroyGameState(GameState* gs)
{
    gs->endPlay();
    delete gs;
}