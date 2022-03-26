#include "GameInstance.hpp"
#include <Core/Global.hpp>
#include <glfw3.h>

UVK::GameInstance::GameInstance() noexcept
{
    actorManager.init();
}

void UVK::GameInstance::exit() noexcept
{
    glfwSetWindowShouldClose(global.window.windowMain, true);
}

UVK::Level* UVK::GameInstance::currentLevel() noexcept
{
    return global.currentLevel;
}