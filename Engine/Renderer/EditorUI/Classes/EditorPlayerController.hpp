// EditorPlayerController.hpp
// Last update 27/8/2021 by Madman10K
#pragma once
#ifndef PRODUCTION
#include <GameFramework/GameplayClasses/PlayerController.hpp>

namespace UVK
{
    class EditorPlayerController : public PlayerController
    {
    public:
        EditorPlayerController();

        virtual void beginPlay() override;
        virtual void tick(float deltaTime) override;
        virtual void endPlay() override;

        ~EditorPlayerController() = default;
    };
}
#endif