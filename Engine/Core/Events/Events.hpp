// Events.hpp
// Last update 7/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../../GameFramework/Actors/ScriptableObject.hpp"

namespace UVK
{
    /**
     * @brief A class to handle calling of events of scriptable objects
     */
    class Events
    {
    public:
        void callTick(float deltaTime);
        void callBegin();
        void callEnd();

        void clear();
        void add(ScriptableObject* sco);
    private:
        std::vector<ScriptableObject*> objList;
    };
}

inline UVK::Events events;