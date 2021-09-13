// ScriptableObject.hpp
// Last update 13/9/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    enum ScriptableObjectActivityFlags
    {
        SCRIPTABLE_OBJECT_ACTIVITY_FLAG_DISABLED, // For an object that will always be disabled
        SCRIPTABLE_OBJECT_ACTIVITY_FLAG_ACTIVE, // For an active object
        SCRIPTABLE_OBJECT_ACTIVITY_FLAG_INACTIVE // For a temporarily inactive object
    };

    class Actor;
    /**
     * @brief A simple class to add additional functionality based on an actor in the scene
     */
    class ScriptableObject
    {
    public:
        ScriptableObject() = default;

        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;
        virtual void inactiveTick(float deltaTime) = 0;
        virtual void inactiveBegin() = 0;
        virtual void inactiveEnd() = 0;

        virtual ~ScriptableObject() = default;

        ScriptableObjectActivityFlags activityFlags;

        template<typename T>
        static T* cast(ScriptableObject* so)
        {
            return static_cast<T*>(so);
        }
    };
}