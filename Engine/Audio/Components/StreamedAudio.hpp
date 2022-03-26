#pragma once
#include "AudioCore.hpp"

namespace UVK
{
#ifndef __MINGW32__
    /**
     * @brief Just a buffer for audio but streamed
     */
    class UVK_PUBLIC_API AudioBufferStreamed
    {
    public:
        AudioBufferStreamed() = default;
        explicit AudioBufferStreamed(String loc, uint32_t chunks) noexcept;

        void addSound(String loc) noexcept;
        void update() noexcept;
        void removeSound() noexcept;

        std::vector<ALuint>& buffer() noexcept;
    private:
        friend class AudioSourceStreamed;

        SNDFILE* sndfile{};
        SF_INFO sndinfo{};
        short* membuf{};
        ALenum format{};
        static constexpr uint32_t samples = 8194;

        std::vector<ALuint> buffers;
        AudioSourceData* data = nullptr;
    };

    /**
     * @brief The physical audio source in the scene but streamed
     */
    class UVK_PUBLIC_API AudioSourceStreamed
    {
    public:
        AudioSourceStreamed();
        void init() noexcept;
        void update(const UVK::FVector& position) noexcept;
        void play() noexcept;

        AudioSourceData& audioData() noexcept;
        AudioBufferStreamed& buffer() noexcept;
        AudioState& state() noexcept;
    private:
        AudioSourceData audioDt;
        AudioBufferStreamed buf;
        AudioState stt{};
    };
#endif
}