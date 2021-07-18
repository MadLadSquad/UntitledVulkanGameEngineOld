// ECS.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    /**
     * @brief A manager responsible for the ECS, not to be confused with the actor manager
     */
    class ECSManager
    {
    public:
        ECSManager() = default;

        void each(std::function<void(entt::entity)> func);

        template<typename T>
        EntityView<T> view()
        {
            return EntityView<T>();
        }

        UVK::EntityPool& data();
        void clear();
    private:
        UVK::EntityPool pool;
    };
}