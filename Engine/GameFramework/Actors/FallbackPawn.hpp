// FallbackPawn.hpp
// Last update 22/9/2021 by Madman10K
#pragma once
#include "Pawn.hpp"

namespace UVK
{
    class FallbackPawn : public UVK::Pawn
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