// FallbackPawn.hpp
// Last update 7/2/2022 by Madman10K
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