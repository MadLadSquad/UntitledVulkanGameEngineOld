// Audio2D.hpp
// Last update 3/2/2021 by Madman10K
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

        /**
         * @brief plays 2D audio
         */
        void play();

        /**
         * @brief Adds sound effect from a file location
         * @param file location string
         * @return Returns a buffer of type ALuint
         */
        ALuint addSoundEffect(const char* filename);

        /**
         * @brief removes a buffer
         * @param buffer to remove
         */
        void removeSoundEffect(ALuint buffer);

        /*
         * @brief initialises our audio
         */
        void init();
    private:

        // cleanup what do you expect?
        void cleanup();

        // Creates and destroys device
        void createDevice();
        void destroyDevice();

        // Creates and destroys sound buffers
        void destroySoundBuffers();
        void createSoundBuffers();

        // Audio device and context
        ALCdevice* device = nullptr;
        ALCcontext* context = nullptr;

        // Array of buffers
        std::vector<ALuint> soundEffectBuffer;
    };

    class SoundSource2D
    {
    public:
        SoundSource2D() = delete;

        /**
         * @brief This constructor creates the audio source
         * @param bLoop true if the sound loops
         * @param nPitch the pitch
         * @param nGain the gain
         */
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

        // Frees up memory
        ~SoundSource2D()
        {
            alDeleteSources(1, &source);
        }

        /**
         * @brief plays a sound from a buffer of type ALuint
         * @param buff the buffer of type ALuint
         */
        void play(ALuint buff);

    private:
        ALuint source = 0;
        float pitch = 1.0f;
        float gain = 1.0f;

        // Position is 0 since this is 2D audio
        float position[3] = { 0, 0, 0 };

        // Velocity
        float velocity[3] = { 0, 0, 0 };
        bool bSoundLoop = true;

        // The buffer
        ALuint buffer = 0;
    };
}

inline UVK::Audio2D audio2d;
#endif