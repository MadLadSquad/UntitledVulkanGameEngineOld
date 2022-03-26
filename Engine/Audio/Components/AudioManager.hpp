#pragma once
#include "AudioCore.hpp"

namespace UVK
{
#ifdef __MINGW32__
    class UVK_PUBLIC_API AudioManager
    {
    public:
        char a = 'a';
    private:
    };
#else
    /**
     * @brief Creates and Destroys an audio device and context
     */
    class UVK_PUBLIC_API AudioManager
    {
    public:
        AudioManager();
        AudioManager(const AudioManager&) = delete;
        void operator=(AudioManager const&) = delete;
        ~AudioManager();

        void createDevice() noexcept;;
        void destroyDevice() noexcept;;
    private:
        ALCdevice* device = nullptr;
        ALCcontext* context = nullptr;
    };
#endif
}