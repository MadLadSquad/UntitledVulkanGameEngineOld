// Events.hpp
// Last update 2/7/2021 by Madman10K
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
        Events() = default;
    private:
        friend class Level;
        friend class GLPipeline;
        friend class Actor;

        void callTick(float deltaTime);
        void callBegin();
        void callEnd();

        void clear();
        void add(ScriptableObject* sco);

        std::vector<ScriptableObject*>& data();
        std::vector<ScriptableObject*> objList;
    };
}