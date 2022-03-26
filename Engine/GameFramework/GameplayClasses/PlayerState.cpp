#include "PlayerState.hpp"

void UVK::PlayerState::destroyPlayerState(PlayerState* ps) noexcept
{
    ps->endPlay();
    delete ps;
}