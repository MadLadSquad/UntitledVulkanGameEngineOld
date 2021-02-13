// Audio2D.cpp
// Last update 2/7/2021 by Madman10K
#include "Audio2D.hpp"

#ifndef __MINGW32__
void UVK::Audio2D::play()
{

}

void UVK::Audio2D::init()
{
    createDevice();
    createSoundBuffers();
}

void UVK::Audio2D::createDevice()
{
    device = alcOpenDevice(nullptr);

    if (!device) logger.consoleLog("Failed to get sound device", ERROR);

    context = alcCreateContext(device, nullptr);

    if (!context) logger.consoleLog("Failed to get sound context", ERROR);
    if (!alcMakeContextCurrent(context)) logger.consoleLog("Failed to use the context", ERROR);

    const ALchar* name = nullptr;

    if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT")) name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
    if (!name || alcGetError(device) != AL_NO_ERROR) name = alcGetString(device, ALC_DEVICE_SPECIFIER);

    logger.consoleLogComplex("Loaded sound device:", SUCCESS, { name });
    logger.consoleLog("Successfully opened a sound device", SUCCESS);
}

void UVK::Audio2D::destroyDevice()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void UVK::Audio2D::cleanup()
{
    destroyDevice();
    destroySoundBuffers();
}

ALuint UVK::Audio2D::addSoundEffect(const char *filename)
{
    ALenum err, format;
    ALuint buffer;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    short* membuf;
    sf_count_t frameNum;
    ALsizei byteNum;

    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (!sndfile)
    {
        logger.consoleLog("Could not open audio file", ERROR);
        return 0;
    }

    if (sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
    {
        logger.consoleLog("Bad sample count", ERROR);
        return 0;
    }

    format = AL_NONE;

    if (sfinfo.channels == 1) format = AL_FORMAT_MONO16;
    else if (sfinfo.channels == 2) format = AL_FORMAT_STEREO16;
    else if (sfinfo.channels == 3)
    {
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) format = AL_FORMAT_BFORMAT2D_16;
    }
    else if (sfinfo.channels == 4)
    {
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) format = AL_FORMAT_BFORMAT3D_16;
    }

    if (!format)
    {
        logger.consoleLog("Unsupported channel count", ERROR);
    }

    membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

    frameNum = sf_readf_short(sndfile, membuf, sfinfo.frames);

    if (frameNum < 1)
    {
        free(membuf);
        sf_close(sndfile);
        logger.consoleLog("Failed to read samples", ERROR);
        return 0;
    }

    byteNum = (ALsizei)(frameNum * sfinfo.channels) * (ALsizei)sizeof(short);

    buffer = 0;

    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, byteNum, sfinfo.samplerate);

    free(membuf);

    sf_close(sndfile);

    err = alGetError();

    if (err != AL_NO_ERROR)
    {
        logger.consoleLogComplex<std::string>("OpenAL Error:", ERROR, { alGetString(err)} );

        if (buffer && alIsBuffer(buffer))
        {
            alDeleteBuffers(1, &buffer);
        }

        return 0;
    }

    soundEffectBuffer.push_back(buffer);

    return buffer;
}

void UVK::Audio2D::removeSoundEffect(ALuint buffer)
{
    // Using iterators here because we need to pass in an iterator for erase
    auto it = soundEffectBuffer.begin();

    while (it != soundEffectBuffer.end())
    {
        if (*it == buffer)
        {
            alDeleteBuffers(1, &*it);

            it = soundEffectBuffer.erase(it);

            return;
        }
        else
        {
            ++it;
        }
    }
}

void UVK::Audio2D::destroySoundBuffers()
{
    alDeleteBuffers(soundEffectBuffer.size(), soundEffectBuffer.data());

    soundEffectBuffer.clear();
}

void UVK::Audio2D::createSoundBuffers()
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
#endif