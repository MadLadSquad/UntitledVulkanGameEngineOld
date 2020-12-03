#pragma once
#include "Defines.h"
#include "../../ThirdParty/EnTT/entt.hpp"
#include "Types.hpp"
#include "../GameFramework/NameComponent.h"



namespace UVK
{
	class Entity
	{
	private:
		/*
			@brief A place where actors are stored
		*/
		Container container;
	public:
		/*
			@brief A hashmap containing all of the actors by name
			@param String - name of the component
			@param Actor - the actor needed to be stored under it's name
		*/
		THashMap<String, Actor> ActorList;

		Entity() {}
		~Entity() {}

		/*
			@brief Creates an actor and adds it to the actor list
			@param Name - the name given to the component. Needed when retrieving a component
		*/
		void CreateActor(String name)
		{
			Actor actor;

			actor = container.create();
			container.emplace<UVK::NameComponent>(actor, name);

			ActorList.insert(std::make_pair(name, actor));
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
			container.emplace<Component>(actor, args...);
		}

		/*
			@brief Removes a given component from an actor
			@tparam component - the component that will be removed
			@param actor - the actor with the component
		*/
		template<typename Component>
		void RemoveComponent(Actor actor)
		{
			container.remove<Component>(actor);
		}

		/*
			@brief Destroys a given actor
			@param actor - the actor needed to be destroyed
		*/
		void DestroyActor(Actor actor)
		{
			container.destroy(actor);
		}

		/*
			@brief Returns a reference to a given component
			@tparam component - the component you need to get a reference to
			@param actor - the actor with the component
		*/
		template<typename Component>
		auto& GetComponent(Actor actor)
		{
			return container.get<Component>(actor);
		}
	};
}