#pragma once
#ifndef PRODUCTION
#include <GameFramework/GameplayClasses/PlayerController.hpp>

namespace UVK
{
    // The player controller used by the editor
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