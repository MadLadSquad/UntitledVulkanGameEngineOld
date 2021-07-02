// ECS.cpp
// Last update 2/7/2021 by Madman10K
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

void UVK::ECSManager::each(std::function<void(entt::entity)> func)
{
    pool.each(std::move(func));
}
