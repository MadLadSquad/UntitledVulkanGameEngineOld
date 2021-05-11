// Renderer.cpp
// Last update 6/5/2021 by Madman10K
#include "Registry.hpp"

void UVK::Registry::createActor(const std::string &name)
{
    Actor act = pool.create();

    auto& a = addComponent<UVK::CoreComponent>(act);
    a.name = name;
    a.id = id;

    id = id++;
}

void UVK::Registry::destroyActor(Actor &act)
{
    pool.destroy(act);
}