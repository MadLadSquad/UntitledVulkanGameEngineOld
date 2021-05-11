// Audio.hpp
// Last update 7/5/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

#ifndef __MINGW32__
namespace UVK
{
    enum AudioState
    {
        UVK_AUDIO_STATE_PAUSED,
        UVK_AUDIO_STATE_RUNNING,
        UVK_AUDIO_STATE_RESUME,
        UVK_AUDIO_STATE_STOPPED
    };
    class AudioManager
    {
    public:
        AudioManager()
        {
            createDevice();
        }

        ~AudioManager()
        {
            destroyDevice();
        }

        void createDevice();
        void destroyDevice();

    private:
        ALCdevice* device = nullptr;
        ALCcontext* context = nullptr;
    };

    class AudioBuffer
    {
    public:
        AudioBuffer() = default;
        explicit AudioBuffer(const char* loc);

        void addSound(const char* loc);
        void removeSound();

        ALuint& getBuffer()
        {
            return buffer;
        }

    private:
        ALuint buffer = 0;
    };

    struct AudioSourceData
    {
        ALuint source;
        float pitch = 1.0f;
        float gain = 1.0f;
        FVector position = FVector(0.0f, 0.0f, 0.0f);
        FVector velocity = FVector(0.0f, 0.0f, 0.0f);
        bool bLoop = false;
    };

    class AudioSource
    {
    public:
        AudioSource() = default;
        AudioSource(const char* loc, AudioSourceData data);

        void play();

        AudioSourceData& getAudioData()
        {
            return audioData;
        }

        AudioBuffer& getBuffer()
        {
            return buffer;
        }

        AudioState& getState()
        {
            return state;
        }
    private:
        AudioSourceData audioData;
        AudioBuffer buffer;
        AudioState state{};
    };
}
inline UVK::AudioManager audio;
#endif
