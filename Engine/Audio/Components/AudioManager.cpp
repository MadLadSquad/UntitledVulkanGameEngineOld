// AudioManager.cpp
// Last update 29/10/2021 by Madman10K
#include "AudioManager.hpp"

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
#endif