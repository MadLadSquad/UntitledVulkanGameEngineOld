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

        // Remove all actors from the scene even if they are deactivated or not rendered
        static void clear() noexcept;
        // Get the internal EntityPool struct
        static EntityPool& data() noexcept;

        // Given a name, id and dev name, this function will return an entity if one is found with these parameters, otherwise, it will return an invalid entity
        static Actor getActorWithIdentifiers(const FString& name, const uint64_t& id, const FString& devname) noexcept;

        // Given a type of component T, this function will iterate all entities with the provided component type and call the callback function specified as the "func" parameter
        template<typename T>
        static void forEveryComponent(const std::function<void(Actor&)>& func) noexcept
        {
            auto view = data().view<T>();
            // we call a function because due to bad dependency management we make a circular dependency
            // here if the code in the call function was called inline here
            for (auto& a : view)
                call(func, a);
        }

        // Given a callback function "func" that takes an argument of type "UVK::Actor&", this function will iterate all actors and call the function on every iteration
        static void each(const std::function<void(Actor&)>& func) noexcept;
    private:
        // This function allows us to not have a circular dependency due to bad dependency management
        static void call(const std::function<void(Actor&)>& func, entt::entity& ent) noexcept;
    };
}