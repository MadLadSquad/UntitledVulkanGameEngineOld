// AudioComponent.cpp
// Last update 6/7/2021 by Madman10K
#include "AudioComponent.hpp"

#include <utility>

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
    src.getState() = UVK_AUDIO_STATE_STOPPED;
#endif
}

void UVK::AudioComponent::pause()
{
#ifndef __MINGW32__
    src.getState() = UVK_AUDIO_STATE_PAUSED;
#endif
}

void UVK::AudioComponent::resume()
{
#ifndef __MINGW32__
    src.getState() = UVK_AUDIO_STATE_RESUME;
#endif
}

void UVK::AudioComponent::init(AudioSourceData dt)
{
    data = std::move(dt);

#ifndef __MINGW32__

#endif
}
