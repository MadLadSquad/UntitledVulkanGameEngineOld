// PlayerState.cpp
// Last update 27/8/2021 by Madman10K
#include "PlayerState.hpp"

void UVK::PlayerState::destroyPlayerState(PlayerState* ps)
{
    ps->endPlay();
    delete ps;
}