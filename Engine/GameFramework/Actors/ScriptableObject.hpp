// ScriptableObject.hpp
// Last update 27/8/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    class Actor;
    /**
     * @brief A simple class to add additional functionality based on an actor in the scene
     */
    class ScriptableObject
    {
    public:
        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;
        virtual ~ScriptableObject() = default;

        template<typename T>
        static T* cast(ScriptableObject* so)
        {
            return static_cast<T*>(so);
        }

        std::string name;
        std::string devname;
        // ids are not universal
        uint64_t id;
        std::vector<Actor*> entities;
    };
}