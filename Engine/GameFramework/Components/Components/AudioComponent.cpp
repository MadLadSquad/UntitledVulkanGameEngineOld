// AudioComponent.cpp
// Last update 7/5/2021 by Madman10K
#include "AudioComponent.hpp"


void UVK::AudioComponent::play(const char* audioLoc)
{
#ifndef __MINGW32__
    src = AudioSource(audioLoc, data);

    src.play();
#endif
}

void UVK::AudioComponent::stop()
{
#ifndef __MINGW32__
    auto& state = src.getState();

    state = UVK_AUDIO_STATE_STOPPED;
#endif
}

void UVK::AudioComponent::pause()
{
#ifndef __MINGW32__
    auto& state = src.getState();

    state = UVK_AUDIO_STATE_PAUSED;
#endif
}

void UVK::AudioComponent::resume()
{
#ifndef __MINGW32__
    auto& state = src.getState();

    state = UVK_AUDIO_STATE_RESUME;
#endif
}

void UVK::AudioComponent::init(FVector position, FVector velocity, float pitch, float gain, bool bLoop)
{
#ifndef __MINGW32__
    data.position = position;
    data.velocity = velocity;
    data.pitch = pitch;
    data.gain = gain;
    data.bLoop = bLoop;
#endif
}
