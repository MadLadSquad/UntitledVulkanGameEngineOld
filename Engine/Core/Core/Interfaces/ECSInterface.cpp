// ECSInterface.cpp
// Last update 1/8/2021 by Madman10K
#include <GL/glew.h>
#include "ECSInterface.hpp"
#include <Core/Global.hpp>

void UVK::ECS::clear()
{
    global.ecs.clear();
}

void UVK::ECS::each(const std::function<void(entt::entity)>& function)
{
    global.ecs.each(function);
}

UVK::EntityPool& UVK::ECS::data()
{
    return global.ecs.data();
}
