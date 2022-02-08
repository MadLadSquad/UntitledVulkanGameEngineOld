// ECS.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <Core/Types.hpp>

namespace UVK
{
    /**
     * @brief A manager responsible for the ECS, not to be confused with the actor manager
     */
    class UVK_PUBLIC_API ECSManager
    {
    public:
        ECSManager() = default;
        ECSManager(const ECSManager&) = delete;
        void operator=(ECSManager const&) = delete;

        template<typename T>
        EntityView<T> view()
        {
            return EntityView<T>(pool);
        }

        UVK::EntityPool& data();
        void clear();
    private:
        UVK::EntityPool pool;
    };
}