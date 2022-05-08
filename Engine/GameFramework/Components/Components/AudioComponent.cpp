#include "AudioComponent.hpp"
#include "CoreComponent.hpp"
#include <Core/Actor.hpp>

void UVK::AudioComponent::create(UVK::Actor* act, const char* file) noexcept
{
    actor = act;

    core = &actor->get<CoreComponent>();
    source = AudioSource();
    source.audioData().location = file;
    source.init();
}

void UVK::AudioComponent::create(UVK::Actor* act) noexcept
{
    actor = act;
    UVK::FString a = source.audioData().location;
    core = &actor->get<CoreComponent>();
    source = AudioSource();
    source.audioData().location = a;
    source.init();
}

void UVK::AudioComponent::create() noexcept
{
    UVK::FString a = source.audioData().location;
    source = AudioSource();
    source.audioData().location = a;
    source.init();
}

void UVK::AudioComponent::tick() noexcept
{
    if (source.state() == UVK_AUDIO_STATE_RUNNING && alGetError() == AL_NO_ERROR)
        source.update(core->translation);
}

bool UVK::AudioComponent::pause() noexcept
{
    if (source.state() == UVK_AUDIO_STATE_RUNNING)
    {
        source.state() = UVK_AUDIO_STATE_PAUSED;
        alSourcePause(source.buffer().buffer());
        return true;
    }
    return false;
}

bool UVK::AudioComponent::stop() noexcept
{
    if (source.state() == UVK_AUDIO_STATE_RUNNING || source.state() == UVK_AUDIO_STATE_PAUSED)
    {
        source.state() = UVK_AUDIO_STATE_STOPPED;
        alSourceStop(source.buffer().buffer());
        alDeleteSources(1, &source.audioData().source);
        source.audioData().source = 0;
        source.buffer().removeSound();
        return true;
    }
    return false;
}

bool UVK::AudioComponent::resume() noexcept
{
    if (source.state() == UVK_AUDIO_STATE_PAUSED)
    {
        source.state() = UVK_AUDIO_STATE_RUNNING;
        alSourcePlay(source.buffer().buffer());
        return true;
    }
    return false;
}

void UVK::AudioComponent::play() noexcept
{
    source.play();
}

void UVK::StreamedAudioComponent::create(UVK::Actor* act, const char* file) noexcept
{
    actor = act;

    core = &actor->get<CoreComponent>();
    source = AudioSourceStreamed();
    source.audioData().location = file;
    source.init();
}

void UVK::StreamedAudioComponent::create(UVK::Actor* act) noexcept
{
    actor = act;
    UVK::FString a = source.audioData().location;
    core = &actor->get<CoreComponent>();
    source = AudioSourceStreamed();
    source.audioData().location = a;
    source.init();
}

void UVK::StreamedAudioComponent::create() noexcept
{
    UVK::FString a = source.audioData().location;
    source = AudioSourceStreamed();
    source.audioData().location = a;
    source.init();
}

void UVK::StreamedAudioComponent::tick() noexcept
{

}

bool UVK::StreamedAudioComponent::pause() noexcept
{
    return false;
}

bool UVK::StreamedAudioComponent::stop() noexcept
{
    return false;
}

bool UVK::StreamedAudioComponent::resume() noexcept
{
    return false;
}

void UVK::StreamedAudioComponent::play() noexcept
{

}
