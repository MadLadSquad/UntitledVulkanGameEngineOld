#pragma once
#include "UUID.hpp"
#include <Core/Global.hpp>

namespace UVK
{
    class UVK_PUBLIC_API Actor
    {
    public:
        Actor() = default;
        explicit Actor(entt::entity ent) noexcept;
        Actor(const std::string& nameN, uint64_t idN, const std::string& devNameN) noexcept;
        bool operator==(entt::entity ent) noexcept;
        bool operator==(Actor actor) noexcept;
        bool operator==(bool) noexcept;
        explicit operator bool() noexcept;

        void create(const std::string& nameN, uint64_t idN, const std::string& devNameN) noexcept;
        bool valid() noexcept;

        template<typename T>
        auto& get() noexcept
        {
            return global.ecs.data().get<T>(entity);
        }

        template<typename T>
        auto& add() noexcept
        {
            return global.ecs.data().emplace_or_replace<T>(entity);
        }

        template<typename T>
        void remove() noexcept
        {
            global.ecs.data().remove<T>(entity);
        }

        template<typename T>
        bool has() noexcept
        {
            return global.ecs.data().any_of<T>(entity);
        }

        // Clears all components from the entity so that it can be used later
        void clear() noexcept;
        void destroy() noexcept;
        entt::entity& data() noexcept;
    private:
        friend class GLRenderer;
        friend class EditorPawn;

        void createInternal(const std::string& nameN, uint64_t idN, const std::string& devNameN, bool bUsingUUID) noexcept;
        entt::entity entity = entt::null;
    };
}