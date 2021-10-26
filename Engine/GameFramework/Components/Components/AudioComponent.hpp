// AudioComponent.hpp
// Last update 26/9/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <Audio/Audio.hpp>

namespace UVK
{
    struct AudioSourceData;
    struct CoreComponent;

    /**
     * @brief A simple audio component
     */
    struct AudioComponent
    {
    public:
        void create(UVK::Actor* act, const char* file);
        void create(UVK::Actor* act);
        void create();

        void tick();

        bool pause();
        bool stop();
        bool resume();
        void play();

        AudioSource source;
    private:
        std::string currentFile;

        UVK::CoreComponent* core = nullptr;
        UVK::Actor* actor = nullptr;
    };
}