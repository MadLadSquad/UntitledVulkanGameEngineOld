// EditorPawn.cpp
// Last update 15/6/2021 by Madman10K
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
    if (UVK::Input::getAction("editor-move").state == Keys::KeyPressed || UVK::Input::getAction("editor-move").state == Keys::KeyRepeat)
    {
        currentWindow.setCursorVisibility(false);

        if (UVK::Input::getAction("editor-move-forward").state == Keys::KeyPressed || UVK::Input::getAction("editor-move-forward").state == Keys::KeyRepeat)
        {
            camera.data().position += camera.data().front * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-back").state == Keys::KeyPressed || UVK::Input::getAction("editor-move-back").state == Keys::KeyRepeat)
        {
            camera.data().position -= camera.data().front * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-left").state == Keys::KeyPressed || UVK::Input::getAction("editor-move-left").state == Keys::KeyRepeat)
        {
            camera.data().position -= camera.data().right * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-right").state == Keys::KeyPressed || UVK::Input::getAction("editor-move-right").state == Keys::KeyRepeat)
        {
            camera.data().position += camera.data().right * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-down").state == Keys::KeyPressed || UVK::Input::getAction("editor-move-down").state == Keys::KeyRepeat)
        {
            camera.data().position -= camera.data().worldUp * moveSpeed * deltaTime;
        }
        if (UVK::Input::getAction("editor-move-up").state == Keys::KeyPressed || UVK::Input::getAction("editor-move-up").state == Keys::KeyRepeat)
        {
            camera.data().position += camera.data().worldUp * moveSpeed * deltaTime;
        }

        auto scroll = UVK::Input::getScroll();

        if (scroll.y > 0)
        {
            camera.data().position += camera.data().front * moveSpeed * deltaTime * 10.0f;
        }
        else if (scroll.y < 0)
        {
            camera.data().position -= camera.data().front * moveSpeed * deltaTime * 10.0f;
        }

        if (scroll.x > 0)
        {
            camera.data().position += camera.data().right * moveSpeed * deltaTime * 10.0f;
        }
        else if (scroll.x < 0)
        {
            camera.data().position -= camera.data().right * moveSpeed * deltaTime * 10.0f;
        }
    }
    else
    {
        currentWindow.setCursorVisibility(true);
    }
}

void UVK::EditorPawn::moveMouse()
{
    if (UVK::Input::getAction("editor-move").state == Keys::KeyPressed || UVK::Input::getAction("editor-move").state == Keys::KeyRepeat)
    {
        auto change = Input::getMousePositionChange();
        change.x *= turnSpeed; //* deltaTime;
        change.y *= turnSpeed; //* deltaTime;

        camera.data().rotation.x += change.x;
        camera.data().rotation.y += change.y;

        if (camera.data().rotation.y > 89.9f)
        {
            camera.data().rotation.y = 89.9f;
        }

        if (camera.data().rotation.y < -89.9f)
        {
            camera.data().rotation.y = -89.9f;
        }
    }

    camera.recalculate();
}

#endif