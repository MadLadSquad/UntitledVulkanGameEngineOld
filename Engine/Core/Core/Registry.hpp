// Registry.hpp
// Last update 2/7/2021 by Madman10K
#include "Engine/GameFramework/Components/Components.hpp"

inline UVK::EntityPool pool;
inline uint64_t id = 0;

namespace UVK
{
    class Registry
    {
    public:
        /**
        * @brief Adds a component to an actor
        * @tparam Component type
        * @param Actor identifier we are adding the component to
        * @return Component reference
        */
        template<typename T>
        auto& addComponent(Actor& act)
        {
            return pool.emplace<T>(act);
        }

        /**
        * @brief Creates an actor from a name
        * @param Name for the actor
        * @return Actor reference
        */
        void createActor(const std::string& name)
        {
            Actor act = pool.create();

            auto& a = addComponent<UVK::CoreComponent>(act);
            a.name = name;
            a.id = id;

            id = id++;
        }

        /**
        * @brief Gets a component from an actor
        * @tparam Type of the component we need to get
        * @param The actor we need to get the component from
        * @return A reference to the component
        */
        template<typename T>
        auto& getComponent(Actor& act)
        {
            return pool.get<T>(act);
        }

        /**
        * @brief Checks if an actor has a component
        * @tparam Component type
        * @param The actor that we need to check
        * @return true if found, false if not found
        */
        template<typename T>
        bool hasComponent(Actor& act)
        {
            return pool.has<T>(act);
        }

        /**
        * @brief Removes a component from an actor
        * @tparam The component that needs to be removed
        * @param The actor that the component needs to be removed from
        * @return void
        */
        template<typename T>
        void removeComponent(Actor& act)
        {
            pool.remove<T>(act);
        }

        /**
         * @brief Destroys an actor
         * @param Actor that needs to be destroyed
         * @return void
         */
        void destroyActor(Actor& act)
        {
            pool.destroy(act);
        }

        /**
        * @brief Iterates the registry and returns actor with a given id
        * @param The id needed for comparison
        * @return An the actor from the registry if found or an empty actor identifier

        Actor& searchByID(uint64_t idNum)
        {
            pool.each([&](Actor act)
            {
                if (pool.has<UVK::CoreComponent>(act))
                {
                    auto& a = pool.get<UVK::CoreComponent>(act);

                    if (a.id == idNum)
                    {
                        return act;
                    }
                }
            });
            Actor act;

            return act;
        };

        /**
        * @brief Iterates the registry and finds an actor with a given name
        * @param The name needed for comparison
        * @return The actor from the registry if found or an empty actor identifier

        Actor& searchByName(std::string name)
        {
            pool.each([&](Actor& act)
            {
                if (pool.has<UVK::CoreComponent>(act))
                {
                    auto& a = pool.get<UVK::CoreComponent>(act);

                    if (a.name == name)
                    {
                        return act;
                    }
                }
            });

            Actor act;
            return act;
        };

        /**
         * @brief Iterates the registry and returns an array of actors that contain a given component
         * @tparam The component needed for comparison
         * @return An array of actor pointers containing the given component

        template<typename T>
        std::vector<Actor*> getAllWithComponent()
        {
            std::vector<Actor*> arr;
            pool.each([&](Actor& act)
            {
                if (pool.has<T>(act))
                {
                    arr.push_back(&act);
                }
            });

            return arr;
        };
        */
    };
}


inline UVK::Registry registry;