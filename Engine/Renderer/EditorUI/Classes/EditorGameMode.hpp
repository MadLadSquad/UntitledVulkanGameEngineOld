#pragma once
#include <GameFramework/GameplayClasses/GameMode.hpp>
#include "EditorPawn.hpp"

#ifndef PRODUCTION
namespace UVK
{
    class UVK_PUBLIC_API EditorGameMode : public GameMode
    {
    public:
        EditorGameMode();

        virtual void beginPlay() override;
        virtual void tick(float deltaTime) override;
        virtual void endPlay() override;
        virtual ~EditorGameMode() override
        {

        }
    };
}
#endif