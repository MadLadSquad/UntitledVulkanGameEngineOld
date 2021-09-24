// EditorPawn.cpp
// Last update 22/9/2021 by Madman10K
#include "EditorPawn.hpp"
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <Core/Actor.hpp>

#ifndef PRODUCTION
void UVK::EditorPawn::beginPlay()
{
    actor = ECS::getActorWithIdentifiers(name, id, devName);

    std::cout << actor.get<CoreComponent>().devName << std::endl;

    coreCache = &actor.get<CoreComponent>();
    camera = Camera::makeCamera(*coreCache, FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f), FVector2(0.1f, 100.0f), 90.0f, Window::windowSize().x / Window::windowSize().y);
}

void UVK::EditorPawn::tick(float deltaTime)
{
    move(deltaTime);
    moveMouse();
}

void UVK::EditorPawn::endPlay()
{

}

void UVK::EditorPawn::move(float deltaTime)
{
    if (UVK::Input::getAction("editor-move") == Keys::KeyPressed || UVK::Input::getAction("editor-move") == Keys::KeyRepeat)
    {
        Window::setCursorVisibility(false);

        if (UVK::Input::getAction("editor-move-forward") == Keys::KeyPressed || UVK::Input::getAction("editor-move-forward") == Keys::KeyRepeat)
        {
            coreCache->translation += camera.front * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-back") == Keys::KeyPressed || UVK::Input::getAction("editor-move-back") == Keys::KeyRepeat)
        {
            coreCache->translation -= camera.front * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-left") == Keys::KeyPressed || UVK::Input::getAction("editor-move-left") == Keys::KeyRepeat)
        {
            coreCache->translation -= camera.right * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-right") == Keys::KeyPressed || UVK::Input::getAction("editor-move-right") == Keys::KeyRepeat)
        {
            coreCache->translation += camera.right * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-down") == Keys::KeyPressed || UVK::Input::getAction("editor-move-down") == Keys::KeyRepeat)
        {
            coreCache->translation -= camera.worldUp * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-up") == Keys::KeyPressed || UVK::Input::getAction("editor-move-up") == Keys::KeyRepeat)
        {
            coreCache->translation += camera.worldUp * moveSpeed * deltaTime;
        }

        auto scroll = UVK::Input::getScroll();

        if (scroll.y > 0)
        {
            coreCache->translation += camera.front * moveSpeed * deltaTime * 10.0f;
        }
        else if (scroll.y < 0)
        {
            coreCache->translation -= camera.front * moveSpeed * deltaTime * 10.0f;
        }

        if (scroll.x > 0)
        {
            coreCache->translation += camera.right * moveSpeed * deltaTime * 10.0f;
        }
        else if (scroll.x < 0)
        {
            coreCache->translation -= camera.right * moveSpeed * deltaTime * 10.0f;
        }
    }
    else
    {
        Window::setCursorVisibility(true);
    }
}

void UVK::EditorPawn::moveMouse()
{
    if (UVK::Input::getAction("editor-move") == Keys::KeyPressed || UVK::Input::getAction("editor-move") == Keys::KeyRepeat)
    {
        auto change = Input::getMousePositionChange();
        change.x *= turnSpeed; //* deltaTime;
        change.y *= turnSpeed; //* deltaTime;

        coreCache->rotation.x += camera.rotationOffset.x + change.x;
        coreCache->rotation.y += camera.rotationOffset.y + change.y;

        if (coreCache->rotation.y > 89.9f)
        {
            coreCache->rotation.y = 89.9f;
        }

        if (coreCache->rotation.y <-89.9f)
        {
            coreCache->rotation.y = -89.9f;
        }

        camera.recalculate();
    }
}

#endif