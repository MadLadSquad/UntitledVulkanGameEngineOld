// Audio.hpp
// Last update 26/10/2021 by Madman10K
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
        AudioSourceData() = default;
        std::string location;
        uint32_t source = 0;
        float pitch = 1.0f;
        float gain = 1.0f;
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
        AudioManager();
        AudioManager(const AudioManager&) = delete;
        void operator=(AudioManager const&) = delete;
        ~AudioManager();

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

        ALuint& buffer();
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
        void init();
        void update(const UVK::FVector& position) const;
        void play();

        AudioSourceData& audioData();
        AudioBuffer& buffer();
        AudioState& state();
    private:
        AudioSourceData audioDt;
        AudioBuffer buf;
        AudioState stt{};
    };
}
#endif