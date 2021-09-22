// GameInstance.hpp
// Last update 22/9/2021 by Madman10K
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

UVK::Level* UVK::GameInstance::currentLevel()
{
    return global.currentLevel;
}