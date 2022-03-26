#pragma once
#include "Pawn.hpp"

namespace UVK
{
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