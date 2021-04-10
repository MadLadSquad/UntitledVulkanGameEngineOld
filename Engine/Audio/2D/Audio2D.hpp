// Audio2D.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include <Core.hpp>

/*
This is the worst audio implementation ever made. There are currently 5 bugs
 1. Bug one is that the program has audio every second time I start it????????????????
 2. For some reason the audio system fucks up my logging system
 3. On top of that the 3D audio doesn't work and sometimes it refuses to start
 4. There is a memory leak here
 5. This is purely me being an inconsistent brainlet retard

This part will probably be rewritten by me on some other smarter guy. Now that I think about this
the whole engine needs to be fixed. I am a literal brainlet retard who decides code patterns based on
how his day was going. I mean for real look at Audio2D.cpp, you can clearly see a malloc and the thing is
I don't use malloc anywhere else. In my Components.hpp class you can see 2 types of design, a get/set and a public variable
This shouldn't be a thing because most of the program is written in a get/set way.
Also the UI is shit, it's low performance. The Filesystem widget doesn't work but this isn't a problem because nothing works
I think I need some time off, I have to finish my english homework and make a presentation for some stupid musician
and am having a maths test in 3 days. Meanwhile I have to release this 0.7.0.0 update while also having to finish the
dev tool for a company that hired me on upwork. I think that this whole engine is a mess and it needs a 5th rewrite.
I hate this engine I hope that nobody sees this code ever and I hope no games will be made with this.

I hate this, I hate OpenAL, I hate OpenGL, I hate GLEW, I hate GLFW, I hate this architecture and finally I hate myself
Thank you for attending my Ted talk, now you can scroll down and look at some shit(govno) code - Madman10K Saturday April 10th 2021
 */
#ifndef __MINGW32__
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <sndfile.h>


namespace UVK
{
    class Audio
    {
    public:
        Audio()
        {
            init();
        }

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
        
    private:
        void init();

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

    class SoundSource3D
    {
    public:
        SoundSource3D() = delete;

        /**
         * @brief This constructor creates the audio source
         * @param bLoop true if the sound loops
         * @param nPitch the pitch
         * @param nGain the gain
         */
        SoundSource3D(bool bLoop, float nPitch, float nGain, FVector pos)
        {
            bSoundLoop = bLoop;
            pitch = nPitch;
            gain = nGain;
            position = pos;
            //buffer = buff;

            alGenSources(1, &source);
            alSourcef(source, AL_PITCH, pitch);
            alSourcef(source, AL_GAIN, gain);
            alSource3f(source, AL_POSITION, position.x, position.y, position.z);
            alSource3f(source, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
            alSourcei(source, AL_LOOPING, bSoundLoop);
            alSourcei(source, AL_BUFFER, buffer);
        }

        // Frees up memory
        ~SoundSource3D()
        {
            alDeleteSources(1, &source);
        }

        /**
         * @brief plays a sound from a buffer of type ALuint
         * @param buff the buffer of type ALuint
         */
        void play(ALuint buff);


        FVector position{};
    private:
        ALuint source = 0;
        float pitch = 1.0f;
        float gain = 1.0f;

        // Velocity
        float velocity[3] = { 0, 0, 0 };
        bool bSoundLoop = true;

        // The buffer
        ALuint buffer = 0;
    };
}

inline UVK::Audio audio;
#endif