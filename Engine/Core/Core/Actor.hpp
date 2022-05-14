#pragma once
#include "UUID.hpp"
#include <Core/Global.hpp>

namespace UVK
{
    // The basic actor abstraction class
    class UVK_PUBLIC_API Actor
    {
    public:
        Actor() = default;
        explicit Actor(entt::entity ent) noexcept;
        Actor(const FString& nameN, uint64_t idN, const FString& devNameN) noexcept;
        bool operator==(entt::entity ent) noexcept;
        bool operator==(Actor actor) noexcept;
        bool operator==(bool) noexcept;
        explicit operator bool() noexcept;

        void create(const FString& nameN, uint64_t idN, const FString& devNameN) noexcept;
        bool valid() noexcept;

        // Returns a component from an actor
        template<typename T>
        inline auto& get() noexcept
        {
            return global.ecs.data().get<T>(entity);
        }

        // Adds a component to an actor
        template<typename T>
        inline auto& add() noexcept
        {
            return global.ecs.data().emplace_or_replace<T>(entity);
        }

        // removes a component from an actor
        template<typename T>
        inline void remove() noexcept
        {
            global.ecs.data().remove<T>(entity);
        }

        // Used to check if the component exists on the actor
        template<typename T>
        inline bool has() noexcept
        {
            return global.ecs.data().any_of<T>(entity);
        }

        // Clears all components from the entity so that it can be used later
        void clear() noexcept;
        // Destroys the entity and its component
        void destroy() noexcept;
        // Returns the internal actor data
        entt::entity& data() noexcept;
    private:
        friend class GLRenderer;
        friend class EditorPawn;

        // An internal function to handle entity creation, the only difference is that the variable "bUsingUUID" exists, which is used to check if the given
        // entity is an engine spawned object
        void createInternal(const FString& nameN, uint64_t idN, const FString& devNameN, bool bUsingUUID) noexcept;
        entt::entity entity = entt::null;
    };
}