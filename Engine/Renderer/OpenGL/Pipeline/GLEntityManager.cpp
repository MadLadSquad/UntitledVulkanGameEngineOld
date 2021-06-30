// GLEntityManager.hpp
// Last update 30/6/2021 by Madman10K
#include <GL/glew.h>
#include <Core/Actor.hpp>
#include "GLEntityManager.hpp"
#include <GameFramework/Components/Components.hpp>

void UVK::GLEntityManager::tick(Camera* camera)
{
    global.ecs.data().each([&](entt::entity ent)
    {
        if (global.ecs.data().has<AudioComponent>(ent))
        {
#ifndef __MINGW32__
            bool bRemove = false;

            {
                auto& audiocmp = global.ecs.data().get<AudioComponent>(ent);

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
                global.ecs.data().remove<AudioComponent>(ent);
            }
#endif
        }

        if (global.ecs.data().has<MeshComponentRaw>(ent))
        {
            auto& a = global.ecs.data().get<MeshComponentRaw>(ent);
            a.render(camera->getProjection().data(), *camera);
        }
    });
}

void UVK::GLEntityManager::clean()
{
    global.ecs.each([&](entt::entity ent)
    {
        if (global.ecs.data().has<MeshComponentRaw>(ent))
        {
            auto& a = global.ecs.data().get<MeshComponentRaw>(ent);

            a.clearMesh();
        }

        if (global.ecs.data().has<AudioComponent>(ent))
        {
#ifndef __MINGW32__
            auto& a = global.ecs.data().get<AudioComponent>(ent);

            a.src.getBuffer().removeSound();
#endif
        }
    });

    global.ecs.clear();
}
