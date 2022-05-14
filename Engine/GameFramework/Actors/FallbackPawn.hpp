#pragma once
#include "Pawn.hpp"

namespace UVK
{
    // Just a pawn to act as a fallback
    class UVK_PUBLIC_API FallbackPawn : public UVK::Pawn
    {
    public:
        FallbackPawn();
        virtual ~FallbackPawn() override = default;

        virtual void beginPlay() override;
        virtual void tick(float deltaTime) override;
        virtual void endPlay() override;

    private:
        UVK::CoreComponent* coreCache = nullptr;
    };
}