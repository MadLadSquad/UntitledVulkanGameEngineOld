// ECS.cpp
// Last update 2/9/2021 by Madman10K
#include "ECS.hpp"

#include <utility>

void UVK::ECSManager::clear()
{
    pool.clear();
}

UVK::EntityPool& UVK::ECSManager::data()
{
    return pool;
}