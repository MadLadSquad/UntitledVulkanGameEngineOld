// GLEntityManager.cpp
// Last update 21/12/2021 by Madman10K
#include "VKEntityManager.hpp"
#include "GameFramework/Components/Components/AudioComponent.hpp"
#include "GameFramework/Components/Components/MeshComponentRaw.hpp"
#include <Core/Global.hpp>

void UVK::VKEntityManager::tick(Camera* camera)
{
    for (const auto& a : global.ecs.data().view<AudioComponent>())
    {
        auto& b = global.ecs.data().get<AudioComponent>(a);
        b.tick();
    }

    for (const auto& a : global.ecs.data().view<MeshComponentRaw>())
    {
        auto& b = global.ecs.data().get<MeshComponentRaw>(a);
        b.render(*camera);
    }
}

void UVK::VKEntityManager::clean()
{
    global.ecs.clear();
}

