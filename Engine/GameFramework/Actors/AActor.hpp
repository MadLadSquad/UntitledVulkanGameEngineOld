// AActor.hpp
// Last update 12/7/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include <Core.hpp>
// To be put in action

namespace UVK
{
    class AActor
    {
    public:


        template<typename T>
        auto& AddComponent(){}

        void CreateActor(){}

        template<typename T>
        auto& GetComponent(){}

        void DestroyActor(){}
    private:
        Actor act;
    };
}
