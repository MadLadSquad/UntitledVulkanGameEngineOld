// AudioComponent.cpp
// Last update 2/7/2021 by Madman10K
#include "AudioComponent.hpp"

void UVK::AudioComponent::play()
{
#ifndef __MINGW32__
    src = AudioSource(data);

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

void UVK::AudioComponent::init(AudioSourceData dt)
{
    data = dt;

#ifndef __MINGW32__

#endif
}
