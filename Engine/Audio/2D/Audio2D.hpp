// Audio2D.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Core.hpp>

#ifndef __MINGW32__
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <sndfile.h>


namespace UVK
{
    class Audio2D
    {
    public:
        void play();

        ALuint addSoundEffect(const char* filename);
        void removeSoundEffect(ALuint buffer);
        void init();
    private:

        void cleanup();

        void createDevice();
        void destroyDevice();

        void destroySoundBuffers();
        void createSoundBuffers();

        ALCdevice* device;
        ALCcontext* context;

        std::vector<ALuint> soundEffectBuffer;
    };

    class SoundSource2D
    {
    public:
        SoundSource2D()
        {
            alGenSources(1, &source);
            alSourcef(source, AL_PITCH, pitch);
            alSourcef(source, AL_GAIN, gain);
            alSource3f(source, AL_POSITION, position[0], position[1], position[2]);
            alSource3f(source, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
            alSourcei(source, AL_LOOPING, bSoundLoop);
            alSourcei(source, AL_BUFFER, buffer);
        }

        ~SoundSource2D()
        {
            alDeleteSources(1, &source);
        }

        void play(ALuint buff);

    private:
        ALuint source;
        float pitch = 1.0f;
        float gain = 1.0f;
        float position[3] = { 0, 0, 0 };
        float velocity[3] = { 0, 0, 0};
        bool bSoundLoop = false;
        ALuint buffer = 0;
    };
}

inline UVK::Audio2D audio2d;
#endif