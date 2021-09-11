// ECSInterface.hpp
// Last update 18/7/2021 by Madman10K
#pragma once
#include <functional>
#include <Core/Types.hpp>

namespace UVK
{
    class Actor;

    class ECS
    {
    public:
        ECS() = delete;
        ECS(const ECS&) = delete;
        void operator=(ECS const&) = delete;

        static void clear();
        static EntityPool& data();

        template<typename T>
        static EntityView<T> view()
        {
            return EntityView<T>();
        }
    };
}