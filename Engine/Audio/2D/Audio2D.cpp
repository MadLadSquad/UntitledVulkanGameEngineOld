// Audio2D.cpp
// Last update 2/2/2021 by Madman10K
#include "Audio2D.hpp"

#ifndef __MINGW32__

void UVK::Audio::init()
{
    createDevice();
    createSoundBuffers();
}

void UVK::Audio::createDevice()
{
    device = alcOpenDevice(nullptr);

    if (!device) logger.consoleLog("Failed to get sound device", UVK_LOG_TYPE_ERROR);

    context = alcCreateContext(device, nullptr);

    if (!context) logger.consoleLog("Failed to get sound context", UVK_LOG_TYPE_ERROR);
    if (!alcMakeContextCurrent(context)) logger.consoleLog("Failed to use the context", UVK_LOG_TYPE_ERROR);

    const ALchar* name = nullptr;

    if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT")) name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
    if (!name || alcGetError(device) != AL_NO_ERROR) name = alcGetString(device, ALC_DEVICE_SPECIFIER);

    logger.consoleLog("Loaded sound device:", UVK_LOG_TYPE_SUCCESS, name);
    logger.consoleLog("Successfully opened a sound device", UVK_LOG_TYPE_SUCCESS);
}

void UVK::Audio::destroyDevice()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void UVK::Audio::cleanup()
{
    destroyDevice();
    destroySoundBuffers();
}

ALuint UVK::Audio::addSoundEffect(const char *filename)
{
    // All the variables we need
    ALenum err, format;
    ALuint buffer;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    short* membuf;
    sf_count_t frameNum;
    ALsizei byteNum;

    // Opens and reads sound file
    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (!sndfile)
    {
        logger.consoleLog("Could not open audio file", UVK_LOG_TYPE_ERROR);
        return 0;
    }

    if (sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
    {
        logger.consoleLog("Bad sample count", UVK_LOG_TYPE_ERROR);
        return 0;
    }

    format = AL_NONE;

    if (sfinfo.channels == 1) format = AL_FORMAT_MONO16;
    else if (sfinfo.channels == 2) format = AL_FORMAT_STEREO16;
    else if (sfinfo.channels == 3)
    {
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) format = AL_FORMAT_BFORMAT2D_16;
    }
    else if (sfinfo.channels == 4)
    {
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) format = AL_FORMAT_BFORMAT3D_16;
    }

    if (!format)
    {
        logger.consoleLog("Unsupported channel count", UVK_LOG_TYPE_ERROR);
    }

    // Allocates memory for the audio buffer
    membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

    frameNum = sf_readf_short(sndfile, membuf, sfinfo.frames);

    if (frameNum < 1)
    {
        free(membuf);
        sf_close(sndfile);
        logger.consoleLog("Failed to read samples", UVK_LOG_TYPE_ERROR);
        return 0;
    }

    byteNum = (ALsizei)(frameNum * sfinfo.channels) * (ALsizei)sizeof(short);

    buffer = 0;

    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, byteNum, sfinfo.samplerate);

    // Freeing up our memory
    free(membuf);

    sf_close(sndfile);

    err = alGetError();

    // Little error check
    if (err != AL_NO_ERROR)
    {
        logger.consoleLog("OpenAL Error:", UVK_LOG_TYPE_ERROR, alGetString(err));

        if (buffer && alIsBuffer(buffer))
        {
            alDeleteBuffers(1, &buffer);
        }

        return 0;
    }

    // Added sound effect to the sound effects buffer array
    soundEffectBuffer.push_back(buffer);

    return buffer;
}

void UVK::Audio::removeSoundEffect(ALuint buffer)
{
    // Using iterators here because we need to pass in an iterator for erase
    auto it = soundEffectBuffer.begin();

    while (it != soundEffectBuffer.end())
    {
        if (*it == buffer)
        {
            alDeleteBuffers(1, &*it);

            soundEffectBuffer.erase(it);

            return;
        }
        else
        {
            ++it;
        }
    }
}

void UVK::Audio::destroySoundBuffers()
{
    alDeleteBuffers(soundEffectBuffer.size(), soundEffectBuffer.data());

    soundEffectBuffer.clear();
}

void UVK::Audio::createSoundBuffers()
{
    soundEffectBuffer.clear();
}

void UVK::SoundSource2D::play(ALuint buff)
{
    if (buff != buffer)
    {
        buffer = buff;

        alSourcei(source, AL_BUFFER, (ALint)buffer);
    }

    alSourcePlay(source);

    ALint state = AL_PLAYING;

    while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
    {
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    }
}

void UVK::SoundSource3D::play(ALuint buff)
{
    if (buff != buffer)
    {
        buffer = buff;

        alSourcei(source, AL_BUFFER, (ALint)buffer);
    }

    alSourcePlay(source);

    ALint state = AL_PLAYING;

    while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
    {
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    }
}
#endif


