// Actor.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <Core/Global.hpp>
#include "UUID.hpp"


namespace UVK
{
    class UVK_PUBLIC_API Actor
    {
    public:
        Actor() = default;
        explicit Actor(entt::entity ent);
        Actor(const std::string& nameN, uint64_t idN, const std::string& devNameN);
        bool operator==(entt::entity ent);
        bool operator==(Actor actor);
        bool operator==(bool);
        explicit operator bool();

        void create(const std::string& nameN, uint64_t idN, const std::string& devNameN);
        bool valid();

        template<typename T>
        auto& get()
        {
            return global.ecs.data().get<T>(entity);
        }

        template<typename T>
        auto& add()
        {
            return global.ecs.data().emplace_or_replace<T>(entity);
        }

        template<typename T>
        void remove()
        {
            global.ecs.data().remove<T>(entity);
        }

        template<typename T>
        bool has()
        {
            return global.ecs.data().any_of<T>(entity);
        }

        // Clears all components from the entity so that it can be used later
        void clear();
        void destroy();
        entt::entity& data();
    private:
        friend class GLRenderer;
        friend class EditorPawn;

        void createInternal(const std::string& nameN, uint64_t idN, const std::string& devNameN, bool bUsingUUID);
        entt::entity entity = entt::null;
    };
}