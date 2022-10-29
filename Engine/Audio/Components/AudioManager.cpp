#include "AudioManager.hpp"

#ifndef __MINGW32__
void UVK::AudioManager::createDevice() noexcept
{
    device = alcOpenDevice(nullptr);

    if (!device)
    {
        Logger::log("Failed to get sound device", UVK_LOG_TYPE_ERROR);
        return;
    }

    context = alcCreateContext(device, nullptr);

    if (!context)
    {
        Logger::log("Failed to get sound context", UVK_LOG_TYPE_ERROR);
        return;
    }

    if (!alcMakeContextCurrent(context))
    {
        Logger::log("Failed to use the context", UVK_LOG_TYPE_ERROR);
        return;
    }

    String name = nullptr;

    if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
        name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
    if (!name || alcGetError(device) != AL_NO_ERROR)
        name = alcGetString(device, ALC_DEVICE_SPECIFIER);
    Logger::log("Loaded sound device \"", UVK_LOG_TYPE_SUCCESS, name, "\"");
}

void UVK::AudioManager::destroyDevice() noexcept
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