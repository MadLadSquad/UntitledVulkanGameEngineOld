// PlayerState.cpp
// Last update 19/7/2021 by Madman10K
#include <GL/glew.h>
#include "PlayerState.hpp"

void UVK::PlayerState::destroyPlayerState(PlayerState* ps)
{
    ps->endPlay();
    delete ps;
}