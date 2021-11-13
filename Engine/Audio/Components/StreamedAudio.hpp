// StreamedAudio.hpp
// Last update 29/10/2021 by Madman10K
#pragma once
#include "AudioCore.hpp"

namespace UVK
{
#ifndef __MINGW32__
    /**
     * @brief Just a buffer for audio but streamed
     */
    class AudioBufferStreamed
    {
    public:
        AudioBufferStreamed() = default;
        explicit AudioBufferStreamed(String loc, uint32_t chunks);

        void addSound(String loc);
        void update();
        void removeSound();

        std::vector<ALuint>& buffer();
    private:
        friend class AudioSourceStreamed;

        SNDFILE* sndfile;
        SF_INFO sndinfo;
        short* membuf;
        ALenum format;
        static constexpr uint32_t samples = 8194;

        std::vector<ALuint> buffers;
        AudioSourceData* data = nullptr;
    };

    /**
 * @brief The physical audio source in the scene but streamed
 */
    class AudioSourceStreamed
    {
    public:
        AudioSourceStreamed();
        void init();
        void update(const UVK::FVector& position);
        void play();

        AudioSourceData& audioData();
        AudioBufferStreamed& buffer();
        AudioState& state();
    private:
        AudioSourceData audioDt;
        AudioBufferStreamed buf;
        AudioState stt{};
    };
#endif
}