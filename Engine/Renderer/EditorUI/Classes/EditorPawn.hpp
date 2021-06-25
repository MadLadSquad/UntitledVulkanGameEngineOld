// EditorPawn.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include <GameFramework/Actors/APawn.hpp>
#include <Renderer/Window/Window.hpp>

#ifndef PRODUCTION
namespace UVK
{
    class EditorPawn : public APawn
    {
    public:
        EditorPawn()
        {
            camera = Camera(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f));
            camera.getProjection().getPlanes() = FVector2(0.1f, 100.0f);
            camera.getProjection().getFOV() = 90.0f;
            camera.getProjection().getAspectRatio() = (GLfloat)currentWindow.getBufferWidth() / (GLfloat)currentWindow.getBufferHeight();
            camera.getProjection().recalculateRH();

            name = "Editor Pawn";
            id = 330;
            devName = "EditorPawn";
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
    };
}
#endif