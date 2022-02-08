// AudioCore.hpp
// Last update 21/12/2021 by Madman10K
#pragma once
#include <Core.hpp>
#ifndef __MINGW32__
    #include <AL/al.h>
    #include <AL/alc.h>
    #include <AL/alext.h>
    #include <sndfile.h>
#endif

namespace UVK
{
    /**
     * @brief States are paused, running, resume, stopped
     */
    enum AudioState
    {
        UVK_AUDIO_STATE_PAUSED,
        UVK_AUDIO_STATE_RUNNING,
        UVK_AUDIO_STATE_STOPPED
    };

    /**
     * @brief All the data that the audio source will ever need
     */
    struct UVK_PUBLIC_API AudioSourceData
    {
        AudioSourceData() = default;
        std::string location;
        uint32_t source = 0;
        float pitch = 1.0f;
        float gain = 1.0f;
        FVector velocity = FVector(0.0f, 0.0f, 0.0f);
        bool bLoop = false;
    };
}