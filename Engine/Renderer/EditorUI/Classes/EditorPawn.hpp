// EditorPawn.hpp
// Last update 22/9/2021 by Madman10K
#pragma once
#include <Engine/Core/Core/Global.hpp>
#include <GameFramework/Actors/Pawn.hpp>
#include <Renderer/Window/Window.hpp>
#include <Core/Actor.hpp>

#ifndef PRODUCTION
namespace UVK
{
    class CoreComponent;

    class EditorPawn : public Pawn
    {
    public:
        EditorPawn()
        {
            name = "Editor Pawn";
            id = 330;
            devName = "EditorPawn";

            actor.create(name, id, devName);
        }

        virtual void beginPlay() override;
        virtual void tick(float deltaTime) override;
        virtual void endPlay() override;
        virtual ~EditorPawn() override
        {

        }

    private:
        void move(float deltaTime);
        void moveMouse();

        float moveSpeed = 5.0f;
        float turnSpeed = 0.5f;

        CoreComponent* coreCache = nullptr;
    };
}
#endif