// Core.hpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include "AActor.hpp"

namespace UVK
{
    UVK_API class APawn : AActor
    {
    public:
        virtual void BeginPlay() override;
        virtual void EndPlay() override;
        virtual void Tick(float DeltaTime) override;
    };
}
