// Audio.hpp
// Last update 4/13/2021 by Madman10K
#pragma once
#include <Audio/AudioSource.hpp>

namespace UVK
{
    class Audio
    {
    public:
        Audio()
        {
            createDevice();
        }

        void createDevice();
        void destroyDevice();

    private:
        ALCdevice* device = nullptr;
        ALCcontext* context = nullptr;
    };
}

inline UVK::Audio audio;