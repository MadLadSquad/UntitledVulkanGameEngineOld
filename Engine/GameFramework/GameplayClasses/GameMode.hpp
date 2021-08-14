// GameMode.hpp
// Last update 19/7/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "GameState.hpp"
#include "PlayerState.hpp"
#include "PlayerController.hpp"
#include "../Actors/APawn.hpp"

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

        GameState* gs = nullptr;
        PlayerState* ps = nullptr;
        PlayerController* pc = nullptr;
        APawn* pawn = nullptr;

        virtual ~GameMode();

        void beginAutohandle() const;
        void tickAutohandle(float deltaTime) const;
        void endAutohandle() const;
    private:
    };

    template<typename T>
    static GameMode* makeGameMode()
    {
        T* gm = new T();
        return gm;
    }

    void destroyGameMode(GameMode* gm);
}
