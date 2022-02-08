// EditorPlayerController.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#ifndef PRODUCTION
#include <GameFramework/GameplayClasses/PlayerController.hpp>

namespace UVK
{
    class UVK_PUBLIC_API EditorPlayerController : public PlayerController
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