// RegularAudio.hpp
// Last update 29/10/2021 by Madman10K
#include "RegularAudio.hpp"

#ifndef __MINGW32__
UVK::AudioBuffer::AudioBuffer(String loc)
{
    addSound(loc);
}

void UVK::AudioBuffer::addSound(String loc)
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

    findFormat(format, sfinfo, sndfile);

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

    alGenBuffers(1, &bufferI);
    alBufferData(bufferI, format, memoryBuffer, byteNum, sfinfo.samplerate);

    free(memoryBuffer);
    sf_close(sndfile);

    error = alGetError();

    if (error != AL_NO_ERROR && error != AL_INVALID_NAME)
    {
        logger.consoleLog("OpenAL error: ", UVK_LOG_TYPE_ERROR, alGetString(error));

        if (bufferI && alIsBuffer(bufferI))
            alDeleteBuffers(1, &bufferI);

        return;
    }
}

void UVK::AudioBuffer::removeSound()
{
    if (alIsBuffer(bufferI) && bufferI)
        alDeleteBuffers(1, &bufferI);
}

ALuint& UVK::AudioBuffer::buffer()
{
    return bufferI;
}

void UVK::AudioBuffer::findFormat(ALenum& format, const SF_INFO& info, SNDFILE* sndfile)
{
    switch (info.channels)
    {
    case 1:
        format = AL_FORMAT_MONO16;
        break;
    case 2:
        format = AL_FORMAT_STEREO16;
        break;
    case 3:
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
            format = AL_FORMAT_BFORMAT2D_16;
        break;
    case 4:
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
            format = AL_FORMAT_BFORMAT3D_16;
        break;
    }

    if (!format)
    {
        logger.consoleLog("Unsupported channel count: ", UVK_LOG_TYPE_ERROR, info.channels);
        sf_close(sndfile);
        sndfile = nullptr;
        return;
    }
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
    alGenSources(1, &audioDt.source);
    buf = AudioBuffer(audioDt.location.c_str());
    update({0.0f, 0.0f, 0.0f});
    alSourcei(audioDt.source, AL_BUFFER, (ALint)buf.buffer());
}
#endif