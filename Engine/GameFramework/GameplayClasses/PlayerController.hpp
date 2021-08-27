// PlayerController.hpp
// Last update 27/8/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../Actors/Pawn.hpp"

namespace UVK
{
    /**
     * @brief A player controller is the so called "soul" of the player. It can possess pawns as well as have
     * the standard events
     */
    class PlayerController
    {
    public:
        PlayerController() = default;

        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        void possess(Pawn* pw);

        Pawn* pawn{};

        virtual ~PlayerController();

        template<typename T>
        static PlayerController* makePlayerController()
        {
            T* pc = new T();
            return pc;
        }

        template<typename T>
        static T* cast(PlayerController* pc)
        {
            return static_cast<T*>(pc);
        }

        static void destroyPlayerController(PlayerController* pc);

        void beginAutohandle() const;
        void tickAutohandle(float deltaTime) const;
        void endAutohandle() const;
    private:
    };
}
