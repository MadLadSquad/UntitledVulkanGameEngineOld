#pragma once
#include <Core.hpp>
#include "../Actors/Pawn.hpp"

namespace UVK
{
    /**
     * @brief A player controller is the so called "soul" of the player. It can possess pawns as well as have
     * the standard events
     */
    class UVK_PUBLIC_API PlayerController
    {
    public:
        PlayerController() = default;

        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        void possess(Pawn* pw) noexcept;

        Pawn* pawn{};

        virtual ~PlayerController() noexcept;

        template<typename T>
        static PlayerController* makePlayerController() noexcept
        {
            T* pc = new T();
            return pc;
        }

        template<typename T>
        static T* cast(PlayerController* pc) noexcept
        {
            return static_cast<T*>(pc);
        }

        static void destroyPlayerController(PlayerController* pc) noexcept;

        void beginAutohandle() const noexcept;
        void tickAutohandle(float deltaTime) const noexcept;
        void endAutohandle() const noexcept;
    private:
    };
}
