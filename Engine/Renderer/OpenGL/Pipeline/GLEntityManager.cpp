// GLEntityManager.hpp
// Last update 19/6/2021 by Madman10K
#include <Core/Registry.hpp>
#include "GLEntityManager.hpp"

void UVK::GLEntityManager::tick(Camera* camera)
{
    pool.each([&](entt::entity ent)
    {
        if (registry.hasComponent<AudioComponent>(ent))
        {
#ifndef __MINGW32__
            bool bRemove = false;

            {
                auto& audiocmp = registry.getComponent<AudioComponent>(ent);

                auto& state = audiocmp.src.getState();

                if (state == UVK_AUDIO_STATE_RESUME)
                {
                    audiocmp.src.play();
                }
                else if (state == UVK_AUDIO_STATE_PAUSED)
                {
                    alSourcePause(audiocmp.src.getBuffer().getBuffer());
                }
                else if (state == UVK_AUDIO_STATE_STOPPED)
                {
                    audiocmp.src.getBuffer().removeSound();
                    bRemove = true;
                }
            }

            if (bRemove)
            {
                registry.removeComponent<AudioComponent>(ent);
            }
#endif
        }

        if (registry.hasComponent<MeshComponentRaw>(ent))
        {
            auto& a = registry.getComponent<MeshComponentRaw>(ent);
            a.render(camera->getProjection().data(), *camera);
        }
    });
}

void UVK::GLEntityManager::clean()
{
    pool.each([&](entt::entity ent)
    {
        if (registry.hasComponent<MeshComponentRaw>(ent))
        {
            auto& a = registry.getComponent<MeshComponentRaw>(ent);

            a.clearMesh();
        }

        if (registry.hasComponent<AudioComponent>(ent))
        {
#ifndef __MINGW32__
            auto& a = registry.getComponent<AudioComponent>(ent);

            a.src.getBuffer().removeSound();
#endif
        }
    });

    pool.clear();
}
