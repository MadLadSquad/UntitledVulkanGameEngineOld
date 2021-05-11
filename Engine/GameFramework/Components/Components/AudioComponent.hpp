// AudioComponent.hpp
// Last update 7/5/2021 by Madman10K
#include <Core.hpp>
#include <Audio/Audio.hpp>

namespace UVK
{
    struct AudioComponent
    {
        void init(FVector position, FVector velocity, float pitch, float gain, bool bLoop);

        void play(const char* audioLoc);
        void stop();
        void pause();
        void resume();

        AudioSourceData data;
        AudioSource src;
    private:
    };
}