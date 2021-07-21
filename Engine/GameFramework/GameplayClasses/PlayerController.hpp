// PlayerController.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../Actors/APawn.hpp"

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

        void possess(APawn* pawn);

        APawn* currentPawn{};

        virtual ~PlayerController();
    private:
    };

    template<typename T>
    static PlayerController* makePlayerController()
    {
        T* pc = new T();
        return pc;
    }

    static void destroyPlayerController(PlayerController* pc);
}
