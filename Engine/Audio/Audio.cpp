// Audio.cpp
// Last update 18/5/2021 by Madman10K
#include "Audio.hpp"
#include <sndfile.h>

#include <utility>

#ifndef __MINGW32__
void UVK::AudioManager::createDevice()
{
    device = alcOpenDevice(nullptr);

    if (!device)
    {
        logger.consoleLog("Failed to get sound device", UVK_LOG_TYPE_ERROR);
    }

    context = alcCreateContext(device, nullptr);

    if (!context)
    {
        logger.consoleLog("Failed to get sound context", UVK_LOG_TYPE_ERROR);
    }
    if (!alcMakeContextCurrent(context))
    {
        logger.consoleLog("Failed to use the context", UVK_LOG_TYPE_ERROR);
    }

    const ALchar* name = nullptr;

    if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
    {
        name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
    }
    if (!name || alcGetError(device) != AL_NO_ERROR)
    {
        name = alcGetString(device, ALC_DEVICE_SPECIFIER);
    }

    logger.consoleLog("Loaded sound device:", UVK_LOG_TYPE_SUCCESS, name);
}

void UVK::AudioManager::destroyDevice()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}


UVK::AudioBuffer::AudioBuffer(const char* loc)
{
    addSound(loc);
}

void UVK::AudioBuffer::addSound(const char* loc)
{
    ALenum error;
    ALenum format;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    short* memoryBuffer;
    sf_count_t frameNum;
    ALsizei byteNum;

    sndfile = sf_open(loc, SFM_READ, &sfinfo);

    if (!sndfile)
    {
        logger.consoleLog("Could not open audio file with location: ", UVK_LOG_TYPE_ERROR, loc);
        return;
    }

    if (sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
    {
        logger.consoleLog("Bad sample count in file: ", UVK_LOG_TYPE_ERROR, loc, ", sample number: ", sfinfo.frames);
        return;
    }

    format = AL_NONE;

    if (sfinfo.channels == 1)
    {
        format = AL_FORMAT_MONO16;
    }
    else if (sfinfo.channels == 2)
    {
        format = AL_FORMAT_STEREO16;
    }
    else if (sfinfo.channels == 3)
    {
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
        {
            format = AL_FORMAT_BFORMAT2D_16;
        }
    }
    else if (sfinfo.channels == 4)
    {
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
        {
            format = AL_FORMAT_BFORMAT3D_16;
        }
    }

    if (!format)
    {
        logger.consoleLog("Unsupported channel count: ", UVK_LOG_TYPE_ERROR, sfinfo.channels);
        sf_close(sndfile);
        return;
    }

    memoryBuffer = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

    frameNum = sf_readf_short(sndfile, memoryBuffer, sfinfo.frames);
    if (frameNum < 1)
    {
        free(memoryBuffer);
        sf_close(sndfile);
        logger.consoleLog("Failed to read samples from file: ", UVK_LOG_TYPE_ERROR, loc, ", with the amount of samples: ", frameNum);
        return;
    }

    byteNum = (ALsizei)(frameNum * sfinfo.channels) * (ALsizei)sizeof(short);
    buffer = 0;

    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, memoryBuffer, byteNum, sfinfo.samplerate);

    free(memoryBuffer);
    sf_close(sndfile);

    error = alGetError();

    if (error != AL_NO_ERROR)
    {
        logger.consoleLog("OpenAL error: ", UVK_LOG_TYPE_ERROR, alGetString(error));

        if (buffer && alIsBuffer(buffer))
        {
            alDeleteBuffers(1, &buffer);
        }

        return;
    }
}

void UVK::AudioBuffer::removeSound()
{
    alDeleteBuffers(1, &buffer);
}

UVK::AudioSource::AudioSource(AudioSourceData data)
{
    audioData = data;
    buffer = AudioBuffer(audioData.location.c_str());

    alGenSources(1, &audioData.source);
    alSourcef(audioData.source, AL_PITCH, audioData.pitch);
    alSourcef(audioData.source, AL_GAIN, audioData.gain);
    alSource3f(audioData.source, AL_POSITION, audioData.position.x, audioData.position.y, audioData.position.z);
    alSource3f(audioData.source, AL_VELOCITY, audioData.velocity.x, audioData.velocity.y, audioData.velocity.z);
    alSourcei(audioData.source, AL_LOOPING, audioData.bLoop);
    alSourcei(audioData.source, AL_BUFFER, (ALint)buffer.getBuffer());

}

void UVK::AudioSource::play()
{
    alSourcePlay(buffer.getBuffer());

    state = UVK_AUDIO_STATE_RUNNING;

    /*while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
    {
        alGetSourcei(audioData.source, AL_SOURCE_STATE, &state);
    }
     */
}
#endif