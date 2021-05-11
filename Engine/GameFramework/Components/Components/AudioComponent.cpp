// AudioComponent.cpp
// Last update 7/5/2021 by Madman10K
#include "AudioComponent.hpp"


void UVK::AudioComponent::play(const char* audioLoc)
{
    src = AudioSource(audioLoc, data);

    src.play();
}

void UVK::AudioComponent::stop()
{
    auto& state = src.getState();

    state = UVK_AUDIO_STATE_STOPPED;
}

void UVK::AudioComponent::pause()
{
    auto& state = src.getState();

    state = UVK_AUDIO_STATE_PAUSED;
}

void UVK::AudioComponent::resume()
{
    auto& state = src.getState();

    state = UVK_AUDIO_STATE_RESUME;
}

void UVK::AudioComponent::init(FVector position, FVector velocity, float pitch, float gain, bool bLoop)
{
    data.position = position;
    data.velocity = velocity;
    data.pitch = pitch;
    data.gain = gain;
    data.bLoop = bLoop;
}
