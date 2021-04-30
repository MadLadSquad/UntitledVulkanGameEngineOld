// Audio2D.cpp
// Last update 4/13/2021 by Madman10K
#include "Audio2D.hpp"

#ifndef __MINGW32__
void UVK::Audio2D::init(const char* location)
{
    ALenum result;
    ALenum format;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    short* membuf;
    sf_count_t framesNum;
    ALsizei bytesNum;

    sndfile = sf_open(location, SFM_READ, &sfinfo);
    if(!sndfile)
    {
        logger.consoleLog("Could not find audio file at location", UVK_LOG_TYPE_ERROR, location);
        return;
    }
    if(sfinfo.frames < 1 || sfinfo.frames > static_cast<sf_count_t>((INT_MAX/sizeof(short))/sfinfo.channels))
    {
        logger.consoleLog("Bad sample count from: ", UVK_LOG_TYPE_ERROR, location);
        sf_close(sndfile);
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
        if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
        {
            format = AL_FORMAT_BFORMAT2D_16;
        }
    }
    else if (sfinfo.channels == 4)
    {
        if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT)
        {
            format = AL_FORMAT_BFORMAT3D_16;
        }
    }

    if(!format)
    {
        logger.consoleLog("Unsupported channel count: ", UVK_LOG_TYPE_ERROR, sfinfo.channels);
        sf_close(sndfile);
        return;
    }

    membuf = static_cast<short*>(malloc(static_cast<size_t>(sfinfo.frames * sfinfo.channels) * sizeof(short)));

    framesNum = sf_readf_short(sndfile, membuf, sfinfo.frames);
    if(framesNum < 1)
    {
        free(membuf);
        sf_close(sndfile);
        logger.consoleLog("Failed to read samples from: ", UVK_LOG_TYPE_ERROR, location);
        return;
    }
    bytesNum = static_cast<ALsizei>(framesNum * sfinfo.channels) * static_cast<ALsizei>(sizeof(short));

    buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, bytesNum, sfinfo.samplerate);

    free(membuf);
    sf_close(sndfile);

    result = alGetError();
    if(result != AL_NO_ERROR)
    {
        logger.consoleLog("Audio error: ", UVK_LOG_TYPE_ERROR, alGetString(result));
        if(buffer && alIsBuffer(buffer))
        {
            alDeleteBuffers(1, &buffer);
        }
        return;
    }
}

void UVK::Audio2D::play()
{

}
#endif