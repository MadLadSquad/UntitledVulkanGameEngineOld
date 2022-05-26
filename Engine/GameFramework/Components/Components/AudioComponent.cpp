#include "AudioComponent.hpp"
#include "CoreComponent.hpp"
#include <Core/Actor.hpp>

namespace YAML
{
    template<>
    struct convert<UVK::FVector>
    {
        static Node encode(const UVK::FVector& rhs) noexcept
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UVK::FVector& rhs) noexcept
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<UVK::FVector4>
    {
        static Node encode(const UVK::FVector4& rhs) noexcept
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UVK::FVector4& rhs) noexcept
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
}

// Operator overloads for future transform component
extern YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector& vect) noexcept;
extern YAML::Emitter& operator<<(YAML::Emitter& out, const UVK::FVector4& vect) noexcept;

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

void UVK::AudioComponent::saveToLevel(YAML::Emitter& out) noexcept
{
    out << YAML::Key << "audio-pitch" << YAML::Value << source.audioData().pitch;
    out << YAML::Key << "audio-gain" << YAML::Value << source.audioData().gain;
    out << YAML::Key << "audio-loop" << YAML::Value << source.audioData().bLoop;
    out << YAML::Key << "audio-velocity" << YAML::Value << source.audioData().velocity;
    out << YAML::Key << "audio-file" << YAML::Value << source.audioData().location.c_str();
}

void UVK::AudioComponent::openToLevel(UVK::Actor& actor, const YAML::Node& entity) noexcept
{
    if (entity["audio-pitch"] && entity["audio-gain"] && entity["audio-loop"] && entity["audio-velocity"] && entity["audio-file"])
    {
        auto& a = actor.add<UVK::AudioComponent>();

        a.source.audioData().pitch = entity["audio-pitch"].as<float>();
        a.source.audioData().gain = entity["audio-gain"].as<float>();
        a.source.audioData().bLoop = entity["audio-loop"].as<bool>();
        a.source.audioData().velocity = entity["audio-velocity"].as<FVector>();
        a.source.audioData().location = entity["audio-file"].as<std::string>();
    }
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
