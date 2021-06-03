// AudioComponent.hpp
// Last update 3/6/2021 by Madman10K
#include <Core.hpp>
#include <Audio/Audio.hpp>

namespace UVK
{
    struct AudioSourceData;

    /**
     * @brief A simple audio component
     */
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