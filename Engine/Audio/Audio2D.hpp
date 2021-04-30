// Audio2D.hpp
// Last update 4/13/2021 by Madman10K
#pragma once
#ifndef __MINGW32__
#include <Audio/AudioSource.hpp>

namespace UVK
{
    class Audio2D
    {
    public:

        void init(const char* location);
        void play();


        void setState(SoundState st)
        {
            state = st;
        }

        [[nodiscard]] SoundState getState() const
        {
            return state;
        }
    private:
        SoundState state;
        ALuint buffer;
    };
}
#endif