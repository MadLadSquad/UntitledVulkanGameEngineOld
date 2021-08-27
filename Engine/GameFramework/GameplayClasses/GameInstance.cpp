// GameInstance.hpp
// Last update 27/8/2021 by Madman10K
#include "GameInstance.hpp"
#include <Core/Global.hpp>

UVK::GameInstance::GameInstance()
{
    actorManager.init();
}

void UVK::GameInstance::exit()
{
    glfwSetWindowShouldClose(global.window.windowMain, true);
}

UVK::GameInstance::~GameInstance()
{
    actorManager.destroy();
}
