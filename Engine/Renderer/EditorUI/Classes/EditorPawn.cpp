// EditorPawn.cpp
// Last update 2/7/2021 by Madman10K
#include "EditorPawn.hpp"

#ifndef PRODUCTION
void UVK::EditorPawn::beginPlay()
{

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
            camera.position += camera.front * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-back") == Keys::KeyPressed || UVK::Input::getAction("editor-move-back") == Keys::KeyRepeat)
        {
            camera.position -= camera.front * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-left") == Keys::KeyPressed || UVK::Input::getAction("editor-move-left") == Keys::KeyRepeat)
        {
            camera.position -= camera.right * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-right") == Keys::KeyPressed || UVK::Input::getAction("editor-move-right") == Keys::KeyRepeat)
        {
            camera.position += camera.right * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-down") == Keys::KeyPressed || UVK::Input::getAction("editor-move-down") == Keys::KeyRepeat)
        {
            camera.position -= camera.worldUp * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-up") == Keys::KeyPressed || UVK::Input::getAction("editor-move-up") == Keys::KeyRepeat)
        {
            camera.position += camera.worldUp * moveSpeed * deltaTime;
        }

        auto scroll = UVK::Input::getScroll();

        if (scroll.y > 0)
        {
            camera.position += camera.front * moveSpeed * deltaTime * 10.0f;
        }
        else if (scroll.y < 0)
        {
            camera.position -= camera.front * moveSpeed * deltaTime * 10.0f;
        }

        if (scroll.x > 0)
        {
            camera.position += camera.right * moveSpeed * deltaTime * 10.0f;
        }
        else if (scroll.x < 0)
        {
            camera.position -= camera.right * moveSpeed * deltaTime * 10.0f;
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

        camera.rotation.x += change.x;
        camera.rotation.y += change.y;

        if (camera.rotation.y > 89.9f)
        {
            camera.rotation.y = 89.9f;
        }

        if (camera.rotation.y < -89.9f)
        {
            camera.rotation.y = -89.9f;
        }
    }

    camera.recalculate();
}

#endif