// AudioComponent.cpp
// Last update 26/9/2021 by Madman10K
#include "AudioComponent.hpp"
#include "CoreComponent.hpp"
#include <Core/Actor.hpp>

void UVK::AudioComponent::create(UVK::Actor* act, const char* file)
{
    actor = act;

    core = &actor->get<CoreComponent>();
    source = AudioSource();
    source.audioData().location = file;
    source.init();
}

void UVK::AudioComponent::create(UVK::Actor* act)
{
    actor = act;
    std::string a = source.audioData().location;
    core = &actor->get<CoreComponent>();
    source = AudioSource();
    source.audioData().location = a;
    source.init();
}

void UVK::AudioComponent::create()
{
    std::string a = source.audioData().location;
    source = AudioSource();
    source.audioData().location = a;
    source.init();
}

void UVK::AudioComponent::tick()
{
    if (source.state() == UVK_AUDIO_STATE_RUNNING && alGetError() == AL_NO_ERROR)
        source.update(core->translation);
}

bool UVK::AudioComponent::pause()
{
    if (source.state() == UVK_AUDIO_STATE_RUNNING)
    {
        source.state() = UVK_AUDIO_STATE_PAUSED;
        alSourcePause(source.buffer().buffer());
        return true;
    }
    return false;
}

bool UVK::AudioComponent::stop()
{
    if (source.state() == UVK_AUDIO_STATE_RUNNING || source.state() == UVK_AUDIO_STATE_PAUSED)
    {
        source.state() = UVK_AUDIO_STATE_STOPPED;
        alSourceStop(source.buffer().buffer());
        alDeleteSources(1, &source.audioData().source);
        source.buffer().removeSound();
        return true;
    }
    return false;
}

bool UVK::AudioComponent::resume()
{
    if (source.state() == UVK_AUDIO_STATE_PAUSED)
    {
        source.state() = UVK_AUDIO_STATE_RUNNING;
        alSourcePlay(source.buffer().buffer());
        return true;
    }
    return false;
}

void UVK::AudioComponent::play()
{
    source.play();
}