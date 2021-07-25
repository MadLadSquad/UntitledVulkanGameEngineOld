// EditorLevel.hpp
// Last update 25/7/2021 by Madman10K
#pragma once
#include "EditorGameMode.hpp"
#include <GameFramework/GameplayClasses/Level/Level.hpp>

#ifndef PRODUCTION
namespace UVK
{
    //class Level;

    class EditorLevel : public Level
    {
    public:
        EditorLevel()
        {
            auto* game = new EditorGameMode();
            gameMode = game;
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