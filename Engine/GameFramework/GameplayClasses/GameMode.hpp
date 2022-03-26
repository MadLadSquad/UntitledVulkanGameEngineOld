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
    class UVK_PUBLIC_API GameMode
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

        void beginAutohandle() const noexcept;
        void tickAutohandle(float deltaTime) const noexcept;
        void endAutohandle() const noexcept;

        [[maybe_unused]] static Pawn* getPawn(UVK::GameMode* gm) noexcept;

        template<typename T>
        static GameMode* makeGameMode() noexcept
        {
            T* gm = new T();
            return gm;
        }

        [[maybe_unused]] static void destroyGameMode(GameMode* gm) noexcept;

        template<typename T>
        static T* cast(GameMode* gm) noexcept
        {
            return static_cast<T*>(gm);
        }
    private:
    };
}
