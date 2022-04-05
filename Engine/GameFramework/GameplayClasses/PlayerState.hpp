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
        [[maybe_unused]] inline static PlayerState* makePlayerState() noexcept
        {
            T* ps = new T();
            return ps;
        }

        template<typename T>
        inline static T* cast(PlayerState* ps) noexcept
        {
            return static_cast<T*>(ps);
        }

        static void destroyPlayerState(PlayerState* ps) noexcept;

        virtual ~PlayerState() = default;
    };
}