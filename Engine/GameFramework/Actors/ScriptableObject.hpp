#pragma once
#include <Core/Defines.hpp>

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
    class UVK_PUBLIC_API ScriptableObject
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

        ScriptableObjectActivityFlags activityFlags = SCRIPTABLE_OBJECT_ACTIVITY_FLAG_ACTIVE;

        template<typename T>
        inline static T* cast(ScriptableObject* so) noexcept
        {
            return static_cast<T*>(so);
        }
    };
}