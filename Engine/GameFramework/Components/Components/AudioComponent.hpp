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
        void create(UVK::Actor* act, const char* file) noexcept;
        void create(UVK::Actor* act) noexcept;
        void create() noexcept;

        void tick() noexcept;

        bool pause() noexcept;
        bool stop() noexcept;
        bool resume() noexcept;
        void play() noexcept;

        AudioSource source;
    private:
        UVK::FString currentFile;

        UVK::CoreComponent* core = nullptr;
        UVK::Actor* actor = nullptr;
    };

    struct UVK_PUBLIC_API StreamedAudioComponent
    {
    public:
        void create(UVK::Actor* act, const char* file) noexcept;
        void create(UVK::Actor* act) noexcept;
        void create() noexcept;

        void tick() noexcept;

        bool pause() noexcept;
        bool stop() noexcept;
        bool resume() noexcept;
        void play() noexcept;

        AudioSourceStreamed source;
    private:
        UVK::FString currentFile;

        UVK::CoreComponent* core = nullptr;
        UVK::Actor* actor = nullptr;
    };
}