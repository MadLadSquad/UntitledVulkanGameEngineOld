// Audio.cpp
// Last update 26/10/2021 by Madman10K
#include "Audio.hpp"
#include <sndfile.h>

#ifndef __MINGW32__
void UVK::AudioManager::createDevice()
{
    device = alcOpenDevice(nullptr);

    if (!device)
    {
        logger.consoleLog("Failed to get sound device", UVK_LOG_TYPE_ERROR);
        return;
    }

    context = alcCreateContext(device, nullptr);

    if (!context)
    {
        logger.consoleLog("Failed to get sound context", UVK_LOG_TYPE_ERROR);
        return;
    }

    if (!alcMakeContextCurrent(context))
    {
        logger.consoleLog("Failed to use the context", UVK_LOG_TYPE_ERROR);
        return;
    }

    String name = nullptr;

    if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
    {
        name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
    }
    if (!name || alcGetError(device) != AL_NO_ERROR)
    {
        name = alcGetString(device, ALC_DEVICE_SPECIFIER);
        return;
    }

    logger.consoleLog("Loaded sound device \"", UVK_LOG_TYPE_SUCCESS, name, "\"");
}

void UVK::AudioManager::destroyDevice()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

UVK::AudioManager::~AudioManager()
{
    destroyDevice();
}

UVK::AudioManager::AudioManager()
{
    createDevice();
}

UVK::AudioBuffer::AudioBuffer(String loc)
{
    addSound(loc);
}

void UVK::AudioBuffer::addSound(String loc)
{
    ALenum error;
    ALenum format;
    SNDFILE* sndfile = nullptr;
    SF_INFO sfinfo;
    short* memoryBuffer = nullptr;
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

    switch (sfinfo.channels)
    {
    case 1:
        format = AL_FORMAT_MONO16;
        break;
    case 2:
        format = AL_FORMAT_STEREO16;
        break;
    case 3:
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
        {
            format = AL_FORMAT_BFORMAT2D_16;
        }
        break;
    case 4:
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
        {
            format = AL_FORMAT_BFORMAT3D_16;
        }
        break;
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
    bufferI = 0;

    ALuint buffs[1] = {bufferI};
    alGenBuffers(1, buffs);
    bufferI = buffs[0];
    alBufferData(bufferI, format, memoryBuffer, byteNum, sfinfo.samplerate);

    free(memoryBuffer);
    sf_close(sndfile);

    error = alGetError();

    if (error != AL_NO_ERROR)
    {
        logger.consoleLog("OpenAL error: ", UVK_LOG_TYPE_ERROR, alGetString(error));

        if (bufferI && alIsBuffer(bufferI))
        {
            ALuint buffers[1] = {bufferI};
            alDeleteBuffers(1, buffers);
        }

        return;
    }
}

void UVK::AudioBuffer::removeSound()
{
    if (alIsBuffer(bufferI) && bufferI)
    {
        ALuint buffers[1] = {bufferI};
        alDeleteBuffers(1, buffers);
    }
}

ALuint& UVK::AudioBuffer::buffer()
{
    return bufferI;
}

void UVK::AudioSource::play()
{
    alSourcePlay(buf.buffer());

    stt = UVK_AUDIO_STATE_RUNNING;
    alSourcei(audioDt.source, AL_SOURCE_STATE, AL_PLAYING);
    /*while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
    {
        alGetSourcei(audioData.source, AL_SOURCE_STATE, &state);
    }
     */
}

UVK::AudioSourceData& UVK::AudioSource::audioData()
{
    return audioDt;
}

UVK::AudioBuffer& UVK::AudioSource::buffer()
{
    return buf;
}

UVK::AudioState& UVK::AudioSource::state()
{
    return stt;
}

void UVK::AudioSource::update(const UVK::FVector& position) const
{
    alSourcef(audioDt.source, AL_PITCH, audioDt.pitch);
    alSourcef(audioDt.source, AL_GAIN, audioDt.gain);
    alSource3f(audioDt.source, AL_POSITION, position.x, position.y, position.z);
    alSource3f(audioDt.source, AL_VELOCITY, audioDt.velocity.x, audioDt.velocity.y, audioDt.velocity.z);
    alSourcei(audioDt.source, AL_LOOPING, audioDt.bLoop);
}

void UVK::AudioSource::init()
{
    buf = AudioBuffer(audioDt.location.c_str());
    uint32_t srcs[1] = {audioDt.source};
    alGenSources(1, srcs);
    audioDt.source = srcs[0];
    update({0.0f, 0.0f, 0.0f});
    alSourcei(audioDt.source, AL_BUFFER, (ALint)buf.buffer());
}

#endif