// GameInstance.hpp
// Last update 21/7/2021 by Madman10K
#include "GameInstance.hpp"
#include <Core/Global.hpp>

UVK::GameInstance::GameInstance()
{
    actorManager.init();
}

UVK::GameInstance::~GameInstance()
{
    actorManager.destroy();
}
