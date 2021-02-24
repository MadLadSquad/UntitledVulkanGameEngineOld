// Components.hpp
// Last update 2/24/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <Audio/2D/Audio2D.hpp>

namespace UVK
{
    UVK_API struct CoreComponent
    {
        std::string name;
        uint64_t id;
    };

    UVK_API struct MeshComponent
    {
        glm::mat4 model;
        FVector translation;
        FVector scale;
        FVector rotation;
        float degrees;
    };

    UVK_API struct PointLightComponent
    {

    };

    UVK_API struct SpotlightComponent
    {

    };

    UVK_API struct DirectionalLightComponent
    {

    };

    struct DirectionalAudioComponent
    {

    };

#ifndef __MINGW32__
    struct AudioComponent2D
    {
    public:
        void play()
        {
            thread = std::thread([&]()
            {
                audio2d.init();
                logger.consoleLog("Initialised audio system", SUCCESS);

                buffer = audio2d.addSoundEffect(loc.c_str());
                logger.consoleLog("Added sound effect", SUCCESS);

                UVK::SoundSource2D src(bRepeat, pitch, gain);

                logger.consoleLog("Playing audio", SUCCESS);
                src.play(buffer);

            });
        }

        void stopAudio()
        {
            thread.join();
        }

        //ALuint& getBuffer()
        //{
        //    return buffer;
        //}

        std::string loc;
        bool bRepeat = false;
        float pitch = 1.0f;
        float gain = 1.0f;
    private:

        ALuint buffer;
        std::thread thread;
    };

#else
    struct AudioComponent2D
    {
        char foo;
        std::string loc;
        bool bRepeat = false;
        float pitch = 1.0f;
        float gain = 1.0f;
    };
#endif
}