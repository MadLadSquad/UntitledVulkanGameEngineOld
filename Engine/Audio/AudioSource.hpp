// AudioSource.hpp
// Last update 4/13/2021 by Madman10K
#pragma once
#ifndef __MINGW32__
#include <Core.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <sndfile.h>

namespace UVK
{
    enum SoundState
    {
        SOUND_STATE_PLAYING,
        SOUND_STATE_PAUSED,
        SOUND_STATE_STOPPED,
        SOUND_STATE_INIT
    };
}

#endif
