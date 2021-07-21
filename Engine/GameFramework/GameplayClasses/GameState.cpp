// GameState.cpp
// Last update 19/7/2021 by Madman10K
#include "GameState.hpp"

void UVK::destroyGameState(GameState* gs)
{
    gs->endPlay();
    delete gs;
}