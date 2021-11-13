// AudioManager.hpp
// Last update 29/10/2021 by Madman10K
#pragma once
#include "AudioCore.hpp"

namespace UVK
{
#ifdef __MINGW32__
    class AudioManager
    {
    public:
        char a = 'a';
    private:
    };
#else
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
#endif
}