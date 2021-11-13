// RegularAudio.hpp
// Last update 29/10/2021 by Madman10K
#pragma once
#include "AudioCore.hpp"

namespace UVK
{
#ifndef __MINGW32__
    /**
     * @brief Just a buffer for audio
     */
    class AudioBuffer
    {
    public:
        AudioBuffer() = default;
        explicit AudioBuffer(String loc);

        void addSound(String loc);
        void removeSound();

        static void findFormat(ALenum& format, const SF_INFO& info, SNDFILE* sndfile);

        ALuint& buffer();
    private:
        ALuint bufferI = 0;
    };

    /**
     * @brief The physical audio source in the scene
     */
    class AudioSource
    {
    public:
        AudioSource() = default;
        void init();
        void update(const UVK::FVector& position) const;
        void play();

        AudioSourceData& audioData();
        AudioBuffer& buffer();
        AudioState& state();
    private:
        AudioSourceData audioDt;
        AudioBuffer buf;
        AudioState stt{};
    };
#endif
}