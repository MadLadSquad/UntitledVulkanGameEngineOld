// GameState.cpp
// Last update 27/8/2021 by Madman10K

#include "GameState.hpp"

void UVK::GameState::destroyGameState(GameState* gs)
{
    gs->endPlay();
    delete gs;
}