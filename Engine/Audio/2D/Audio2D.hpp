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
        Audio2D() = default;

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

        ALCdevice* device = nullptr;
        ALCcontext* context = nullptr;

        std::vector<ALuint> soundEffectBuffer;
    };

    class SoundSource2D
    {
    public:
        SoundSource2D() = delete;

        SoundSource2D(bool bLoop, float nPitch, float nGain)
        {
            bSoundLoop = bLoop;
            pitch = nPitch;
            gain = nGain;

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
        ALuint source = 0;
        float pitch = 1.0f;
        float gain = 1.0f;
        float position[3] = { 0, 0, 0 };
        float velocity[3] = { 0, 0, 0 };
        bool bSoundLoop = true;
        ALuint buffer = 0;
    };
}

inline UVK::Audio2D audio2d;
#endif