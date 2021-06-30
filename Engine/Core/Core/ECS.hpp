// ECS.hpp
// Last update 30/6/2021 by Madman10K
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

        UVK::EntityPool& data();
        void clear();
    private:
        UVK::EntityPool pool;
    };
}