// AudioComponent.hpp
// Last update 7/5/2021 by Madman10K
#include <Core.hpp>
#include <Audio/Audio.hpp>

namespace UVK
{
    struct AudioComponent
    {
        void init(AudioSourceData dt);

        void play();
        void stop();
        void pause();
        void resume();

#ifndef __MINGW32__
        AudioSourceData data;
        AudioSource src;
#endif
    private:
    };
}