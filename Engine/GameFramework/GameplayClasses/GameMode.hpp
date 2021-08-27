// GameMode.hpp
// Last update 27/8/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "GameState.hpp"
#include "PlayerState.hpp"
#include "PlayerController.hpp"
#include "../Actors/Pawn.hpp"

namespace UVK
{
    /**
     * @brief A game mode contains pointers to a GameState, PlayerState, PlayerController and a Pawn
     */
    class GameMode
    {
    public:
        GameMode() = default;

        virtual void beginPlay() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void endPlay() = 0;

        GameState* gameState = nullptr;
        PlayerState* playerState = nullptr;
        PlayerController* playerController = nullptr;

        virtual ~GameMode();

        void beginAutohandle() const;
        void tickAutohandle(float deltaTime) const;
        void endAutohandle() const;

        static Pawn* getPawn(UVK::GameMode* gm);

        template<typename T>
        static GameMode* makeGameMode()
        {
            T* gm = new T();
            return gm;
        }

        static void destroyGameMode(GameMode* gm);

        template<typename T>
        static T* cast(GameMode* gm)
        {
            return static_cast<T*>(gm);
        }
    private:
    };
}
