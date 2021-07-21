// PlayerState.cpp
// Last update 19/7/2021 by Madman10K
#include "PlayerState.hpp"

void UVK::destroyPlayerState(PlayerState* ps)
{
    ps->endPlay();
    delete ps;
}