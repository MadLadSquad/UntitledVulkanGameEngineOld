// GameInstance.hpp
// Last update 2/7/2021 by Madman10K
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