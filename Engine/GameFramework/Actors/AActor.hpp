// AActor.hpp
// Last update 1/10/2021 by Madman10K
#pragma once
#include <Core.hpp>
// To be put in action

namespace UVK
{
    class AActor
    {
    public:
        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;
    };
}
