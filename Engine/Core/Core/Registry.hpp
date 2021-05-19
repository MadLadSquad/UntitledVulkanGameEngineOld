// Registry.hpp
// Last update 18/5/2021 by Madman10K
#include "Engine/GameFramework/Components/Components.hpp"

inline UVK::EntityPool pool;

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
        void createActor(const std::string& name);

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
        static void destroyActor(Actor& act);
    };
}


inline UVK::Registry registry;