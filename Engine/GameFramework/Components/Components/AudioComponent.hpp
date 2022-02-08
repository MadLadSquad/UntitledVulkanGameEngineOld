// AudioComponent.hpp
// Last update 7/2/2022 by Madman10K
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
    struct UVK_PUBLIC_API AudioComponent
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

    struct UVK_PUBLIC_API StreamedAudioComponent
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

        AudioSourceStreamed source;
    private:
        std::string currentFile;

        UVK::CoreComponent* core = nullptr;
        UVK::Actor* actor = nullptr;
    };
}