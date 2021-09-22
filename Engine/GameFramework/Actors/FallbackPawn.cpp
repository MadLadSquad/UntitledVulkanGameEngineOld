// FallbackPawn.cpp
// Last update 22/9/2021 by Madman10K
#include "FallbackPawn.hpp"
#include <GameFramework/Components/Components/CoreComponent.hpp>

UVK::FallbackPawn::FallbackPawn()
{
    name = "Editor Fallback Pawn";
    id = 330;
    devName = "EditorFallbackPawn";

    actor = Actor(name, id, devName);
}

void UVK::FallbackPawn::beginPlay()
{
    coreCache = &actor.get<CoreComponent>();
    camera = Camera::makeCamera(*coreCache, FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f), FVector2(0.1f, 100.0f), 90.0f, Window::windowSize().x / Window::windowSize().y);
}

void UVK::FallbackPawn::tick(float deltaTime)
{

}

void UVK::FallbackPawn::endPlay()
{
    coreCache = nullptr;
}
