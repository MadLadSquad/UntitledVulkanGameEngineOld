#pragma once
#include "AudioCore.hpp"

namespace UVK
{
#ifndef __MINGW32__
    /**
     * @brief Just a buffer for audio
     */
    class UVK_PUBLIC_API AudioBuffer
    {
    public:
        AudioBuffer() = default;
        explicit AudioBuffer(String loc);

        void addSound(String loc) noexcept;
        void removeSound() noexcept;

        static void findFormat(ALenum& format, const SF_INFO& info, SNDFILE* sndfile) noexcept;

        ALuint& buffer() noexcept;
    private:
        ALuint bufferI = 0;
    };

    /**
     * @brief The physical audio source in the scene
     */
    class UVK_PUBLIC_API AudioSource
    {
    public:
        AudioSource() = default;
        void init() noexcept;
        void update(const UVK::FVector& position) const noexcept;
        void play() noexcept;

        AudioSourceData& audioData() noexcept;
        AudioBuffer& buffer() noexcept;
        AudioState& state() noexcept;
    private:
        AudioSourceData audioDt;
        AudioBuffer buf;
        AudioState stt{};
    };
#endif
}