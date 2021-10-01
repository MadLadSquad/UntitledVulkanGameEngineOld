// GLEntityManager.hpp
// Last update 22/9/2021 by Madman10K
#include <Core/Actor.hpp>
#include "GLEntityManager.hpp"
#include <GameFramework/Components/Components.hpp>

void UVK::GLEntityManager::tick(Camera* camera)
{
    //for (const auto& a : global.ecs.data().view<AudioComponent>())
    //{
    //    {
    //        auto& audiocmp = global.ecs.data().get<AudioComponent>(a);
    //        auto& state = audiocmp.src.state();
    //        switch (state)
    //        {
    //            case UVK_AUDIO_STATE_RESUME:
    //                audiocmp.src.play();
    //                break;
    //            case UVK_AUDIO_STATE_PAUSED:
    //                alSourcePause(audiocmp.src.buffer().buffer());
    //                break;
    //            case UVK_AUDIO_STATE_STOPPED:
    //                audiocmp.src.buffer().removeSound();
    //                state = UVK_AUDIO_STATE_PAUSED;
    //                break;
    //            case UVK_AUDIO_STATE_RUNNING:
    //                break;
    //        }
    //        //else if (state == UVK_AUDIO_STATE_STOPPED)
    //        //{
    //        //    audiocmp.src.getBuffer().removeSound();
    //        //    bRemove = true;
    //        //}
    //    }
    //}

    for (const auto& a : global.ecs.data().view<MeshComponentRaw>())
    {
        auto& b = global.ecs.data().get<MeshComponentRaw>(a);
        b.render(camera->projection().data(), *camera);
    }
}

void UVK::GLEntityManager::clean()
{
    global.ecs.clear();
}
