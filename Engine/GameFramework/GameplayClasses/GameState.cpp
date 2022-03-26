#include "GameState.hpp"

void UVK::GameState::destroyGameState(GameState* gs) noexcept
{
    gs->endPlay();
    delete gs;
}