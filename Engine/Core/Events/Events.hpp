// Events.hpp
// Last update 30/6/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    class ScriptableObject;
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

        std::vector<ScriptableObject*>& data();
    private:
        std::vector<ScriptableObject*> objList;
    };
}

inline UVK::Events events;