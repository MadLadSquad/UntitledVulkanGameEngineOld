// ECSInterface.hpp
// Last update 18/7/2021 by Madman10K
#pragma once
#include <functional>
#include <Core/Types.hpp>

namespace UVK
{
    class ECS
    {
    public:
        static void clear();
        static void each(const std::function<void(entt::entity)>& function);
        static EntityPool& data();

        template<typename T>
        static EntityView<T> view()
        {
            return EntityView<T>();
        }
    };
}