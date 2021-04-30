// Audio.cpp
// Last update 4/13/2021 by Madman10K
#include "Audio.hpp"
#ifndef __MINGW32__
void UVK::Audio::createDevice()
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
    logger.consoleLog("Successfully opened a sound device", UVK_LOG_TYPE_SUCCESS);
}

void UVK::Audio::destroyDevice()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
#endif