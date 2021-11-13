// StreamedAudio.hpp
// Last update 29/10/2021 by Madman10K
#include "StreamedAudio.hpp"
#include "RegularAudio.hpp"

#ifndef __MINGW32__
UVK::AudioBufferStreamed::AudioBufferStreamed(UVK::String loc, uint32_t chunks)
{
    buffers.resize(chunks);
    addSound(loc);
}

void UVK::AudioBufferStreamed::addSound(String loc)
{
    alGenSources(1, &data->source);
    alGenBuffers(buffers.size(), buffers.data());

    size_t frameSize;
    sndfile = sf_open(loc, SFM_READ, &sndinfo);
    if (!sndfile)
    {
        logger.consoleLog("Could not open audio file with location: ", UVK_LOG_TYPE_ERROR, loc);
        return;
    }

    AudioBuffer::findFormat(format, sndinfo, sndfile);

    frameSize = ((size_t)samples * (size_t)sndinfo.channels) * sizeof(short);
    membuf = static_cast<short*>(malloc(frameSize));
}

std::vector<ALuint>& UVK::AudioBufferStreamed::buffer()
{
    return buffers;
}

void UVK::AudioBufferStreamed::removeSound()
{
    alDeleteSources(1, &data->source);
    if (sndfile)
        sf_close(sndfile);
    free(membuf);
    alDeleteBuffers(buffers.size(), buffers.data());
}

void UVK::AudioBufferStreamed::update()
{

}

void UVK::AudioSourceStreamed::init()
{

    alGetError(); // Clear out the errors
    alSourceRewind(audioDt.source);
    alSourcei(audioDt.source, AL_BUFFER, 0);

    for (uint32_t& buffera : buffer().buffers)
    {
        sf_count_t slen = sf_read_short(buffer().sndfile, buffer().membuf, AudioBufferStreamed::samples);
        if (slen < 1)
            break;

        slen *= buffer().sndinfo.channels * (sf_count_t)sizeof(short);
        alBufferData(buffera, buffer().format, buffer().membuf, (ALsizei)slen, buffer().sndinfo.samplerate);
    }

    if (alGetError() != AL_NO_ERROR)
    {
        logger.consoleLog("Error when buffering for playing!", UVK_LOG_TYPE_ERROR);
        return;
    }

    alSourceQueueBuffers(audioDt.source, buffer().buffers.size(), buffer().buffers.data());
    alSourcePlay(audioDt.source);

    if (alGetError() != AL_NO_ERROR)
    {
        logger.consoleLog("Error starting playback!", UVK_LOG_TYPE_ERROR);
        return;
    }
}

void UVK::AudioSourceStreamed::update(const UVK::FVector& position)
{
    ALint processed, state;
    alGetError(); // Clear all the errors

    alGetSourcei(audioDt.source, AL_SOURCE_STATE, &state);
    alGetSourcei(audioDt.source, AL_BUFFERS_PROCESSED, &processed);

    if (alGetError() != AL_NO_ERROR)
    {
        logger.consoleLog("Error when checking audio source state", UVK_LOG_TYPE_ERROR);
        return;
    }

    while (processed > 0)
    {
        ALuint bufid;
        sf_count_t slen;

        alSourceUnqueueBuffers(audioDt.source, 1, &bufid);
        processed--;

        slen = sf_readf_short(buffer().sndfile, buffer().membuf, AudioBufferStreamed::samples);
        if (slen > 0)
        {
            slen *= buffer().sndinfo.channels * (sf_count_t)sizeof(short);
            alBufferData(bufid, buffer().format, buffer().membuf, (ALsizei)slen, buffer().sndinfo.samplerate);
            alSourceQueueBuffers(audioDt.source, 1, &bufid);
        }
        if (alGetError() != AL_NO_ERROR)
        {
            logger.consoleLog("Error when buffering audio data", UVK_LOG_TYPE_ERROR);
            return;
        }
    }

    if (state != AL_PLAYING && state != AL_PAUSED)
    {
        ALint queued;
        alGetSourcei(audioDt.source, AL_BUFFERS_QUEUED, &queued);
        if (queued == 0)
            return;

        alSourcePlay(audioDt.source);
        if (alGetError() != AL_NO_ERROR)
            logger.consoleLog("Error when restarting audio playback", UVK_LOG_TYPE_ERROR);
    }
}

void UVK::AudioSourceStreamed::play()
{

}

UVK::AudioSourceData& UVK::AudioSourceStreamed::audioData()
{
    return audioDt;
}

UVK::AudioBufferStreamed &UVK::AudioSourceStreamed::buffer()
{
    return buf;
}

UVK::AudioState& UVK::AudioSourceStreamed::state()
{
    return stt;
}

UVK::AudioSourceStreamed::AudioSourceStreamed()
{
    buf.data = &audioDt;
}
#endif