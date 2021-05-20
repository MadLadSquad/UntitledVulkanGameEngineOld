// AudioComponent.hpp
// Last update 7/5/2021 by Madman10K
#include <Core.hpp>
#include <Audio/Audio.hpp>

namespace UVK
{
    struct AudioSourceData;

    struct AudioComponent
    {
        void init(AudioSourceData dt);

        void play();
        void stop();
        void pause();
        void resume();


        AudioSourceData data;
#ifndef __MINGW32__
        AudioSource src;
#endif
    private:
    };
}