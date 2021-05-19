// GameInstance.hpp
// Last update 18/5/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    class GameInstance
    {
    public:
        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;

        virtual ~GameInstance() = default;
    };
}