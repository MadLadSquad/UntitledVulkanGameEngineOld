// GameInstance.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    /**
     * @brief The instance of the application
     */
    class GameInstance
    {
    public:
        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;

        virtual ~GameInstance() = default;
    };
}