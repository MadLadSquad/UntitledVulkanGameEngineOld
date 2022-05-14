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

        // Returns a view, a collection of actors based on their components that can be iterated
        template<typename T>
        inline EntityView<T> view() noexcept
        {
            return EntityView<T>(pool);
        }

        // Returns the internal pool data
        UVK::EntityPool& data() noexcept;
        // Removes all entities from the pool
        void clear() noexcept;
    private:
        UVK::EntityPool pool;
    };
}