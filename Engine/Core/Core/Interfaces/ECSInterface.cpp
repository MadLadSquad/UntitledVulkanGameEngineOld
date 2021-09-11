// ECSInterface.cpp
// Last update 2/9/2021 by Madman10K
#include "ECSInterface.hpp"
#include <Core/Global.hpp>

void UVK::ECS::clear()
{
    global.ecs.clear();
}

UVK::EntityPool& UVK::ECS::data()
{
    return global.ecs.data();
}
