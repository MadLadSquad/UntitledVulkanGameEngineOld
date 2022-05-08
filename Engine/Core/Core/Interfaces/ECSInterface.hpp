#pragma once
#include <functional>
#include <Core/Types.hpp>

namespace UVK
{
    class Actor;

    class UVK_PUBLIC_API ECS
    {
    public:
        ECS() = delete;
        ECS(const ECS&) = delete;
        void operator=(ECS const&) = delete;

        static void clear() noexcept;
        static EntityPool& data() noexcept;

        static Actor getActorWithIdentifiers(const FString& name, const uint64_t& id, const FString& devname) noexcept;

        template<typename T>
        static void forEveryComponent(const std::function<void(Actor&)>& func) noexcept
        {
            auto view = data().view<T>();
            // we call a function because due to bad dependency management we make a circular dependency
            // here if the code in the call function was called inline here
            for (auto& a : view)
                call(func, a);
        }

        static void each(const std::function<void(Actor&)>& func) noexcept;
    private:
        static void call(const std::function<void(Actor&)>& func, entt::entity& ent) noexcept;
    };
}