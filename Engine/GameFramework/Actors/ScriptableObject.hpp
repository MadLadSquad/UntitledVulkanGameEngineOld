// ScriptableObject.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
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

        std::string name;
        std::string devname;
        // ids are not universal
        uint64_t id;
        std::vector<Actor*> entities;
    };
}