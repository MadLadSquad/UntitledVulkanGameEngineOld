#pragma once
#include "EditorGameMode.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>

#ifndef PRODUCTION
namespace UVK
{
    //class Level;

    class UVK_PUBLIC_API EditorLevel : public Level
    {
    public:
        EditorLevel()
        {
            gameMode = GameMode::makeGameMode<EditorGameMode>();
        }

        virtual void beginPlay() override;
        virtual void tick(float deltaTime) override;
        virtual void endPlay() override;

        virtual ~EditorLevel()
        {

        }
    };
}
#endif