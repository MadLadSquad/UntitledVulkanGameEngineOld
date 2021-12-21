// GameInstance.hpp
// Last update 21/12/2021 by Madman10K
#include "GameInstance.hpp"
#include <Core/Global.hpp>
#include <glfw3.h>

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