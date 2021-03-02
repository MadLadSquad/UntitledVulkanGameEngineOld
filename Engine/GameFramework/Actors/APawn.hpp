// APawn.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "ScriptableObject.hpp"

namespace UVK
{
    /**
     * @brief an actor that the player can control
     */
    UVK_API class APawn
    {
    public:
        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        virtual ~APawn() = default;
    };
}
