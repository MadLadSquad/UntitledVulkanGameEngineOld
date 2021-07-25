// Audio.hpp
// Last update 25/7/2021 by Madman10K
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

        ALuint& buffer()
        {
            return bufferI;
        }

    private:
        ALuint bufferI = 0;
    };

    /**
     * @brief The physical audio source in the scene
     */
    class AudioSource
    {
    public:
        AudioSource() = default;
        explicit AudioSource(const AudioSourceData& data);

        void play();

        AudioSourceData& audioData()
        {
            return audioDt;
        }

        AudioBuffer& buffer()
        {
            return buf;
        }

        AudioState& state()
        {
            return stt;
        }
    private:
        AudioSourceData audioDt;
        AudioBuffer buf;
        AudioState stt{};
    };
}
#endif