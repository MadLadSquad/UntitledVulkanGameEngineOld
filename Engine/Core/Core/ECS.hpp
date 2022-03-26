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
        EntityView<T> view() noexcept
        {
            return EntityView<T>(pool);
        }

        UVK::EntityPool& data() noexcept;
        void clear() noexcept;
    private:
        UVK::EntityPool pool;
    };
}