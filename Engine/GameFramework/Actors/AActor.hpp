// AActor.hpp
// Last update 12/7/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include <Core.hpp>
#include "../Components/Components.hpp"

namespace UVK
{
    UVK_API class AActor
    {
        EntityPool entityPool;
    public:
        EntityPool& GetEntityPool()
        {
            return entityPool;
        }

        /*
            @brief Creates an actor and adds it to the actor list
            @param Name - the name given to the component. Needed when retrieving a component
        */
        void CreateActor(String name)
        {
            Actor actor;

            actor = entityPool.create();
            entityPool.emplace<UVK::NameComponent>(actor, name);
        }

        /*
            @brief Adds a new component to an actor
            @tparam component - the component you need to get a reference to
            @tparam Args - the value/s you need to set to a component
            @param actor - the actor with the component
            @param args - the value/s you need to set to a component
        */
        template<typename Component, typename...Args>
        void AddComponent(Actor actor, Args...args)
        {
            entityPool.emplace<Component>(actor, args...);
        }

        /*
            @brief Removes a given component from an actor
            @tparam component - the component that will be removed
            @param actor - the actor with the component
        */
        template<typename Component>
        void RemoveComponent(Actor actor)
        {
            entityPool.remove<Component>(actor);
        }

        /*
            @brief Destroys a given actor
            @param actor - the actor needed to be destroyed
        */
        void DestroyActor(Actor actor)
        {
            entityPool.destroy(actor);
        }

        /*
            @brief Returns a reference to a given component
            @tparam component - the component you need to get a reference to
            @param actor - the actor with the component
        */
        template<typename Component>
        auto& GetComponent(Actor actor)
        {
            return entityPool.get<Component>(actor);
        }

        virtual void BeginPlay() = 0;
        virtual void Tick(float DeltaTime) = 0;
        virtual void EndPlay() = 0;
    };
}
