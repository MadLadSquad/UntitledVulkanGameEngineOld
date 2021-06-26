// Audio.hpp
// Last update 26/6/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    /**
     * @brief States are paused, running, resume, stopped
     */
    enum AudioState
    {
        UVK_AUDIO_STATE_PAUSED,
        UVK_AUDIO_STATE_RUNNING,
        UVK_AUDIO_STATE_RESUME,
        UVK_AUDIO_STATE_STOPPED
    };

#ifdef __MINGW32__
    class AudioManager
    {
    public:
        char a = 'a';
    private:
    };
#endif
    class AudioBuffer;
    struct AudioSourceData;
    class AudioSource;

    /**
     * @brief All the data that the audio source will ever need
     */
    struct AudioSourceData
    {
        std::string location;
        uint32_t source;
        float pitch = 1.0f;
        float gain = 1.0f;
        FVector position = FVector(0.0f, 0.0f, 0.0f);
        FVector velocity = FVector(0.0f, 0.0f, 0.0f);
        bool bLoop = false;
    };
}

#ifndef __MINGW32__
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

namespace UVK
{
    /**
     * @brief Creates and Destroys an audio device and context
     */
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

    /**
     * @brief Just a buffer for audio
     */
    class AudioBuffer
    {
    public:
        AudioBuffer() = default;
        explicit AudioBuffer(String loc);

        void addSound(String loc);
        void removeSound();

        ALuint& getBuffer()
        {
            return buffer;
        }

    private:
        ALuint buffer = 0;
    };

    /**
     * @brief The physical audio source in the scene
     */
    class AudioSource
    {
    public:
        AudioSource() = default;
        explicit AudioSource(AudioSourceData data);

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
#endif