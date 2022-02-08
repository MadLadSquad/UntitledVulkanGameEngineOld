// PlayerState.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <Core.hpp>
#include "../Actors/Pawn.hpp"

namespace UVK
{
    /**
     * @brief A player state is a simple class that semantically should be used to track the state of the player
     */
    class UVK_PUBLIC_API PlayerState
    {
    public:
        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        template<typename T>
        static PlayerState* makePlayerState()
        {
            T* ps = new T();
            return ps;
        }

        template<typename T>
        static T* cast(PlayerState* ps)
        {
            return static_cast<T*>(ps);
        }

        static void destroyPlayerState(PlayerState* ps);

        virtual ~PlayerState() = default;
    };
}