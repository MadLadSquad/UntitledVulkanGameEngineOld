// Events.hpp
// Last update 13/9/2021 by Madman10K
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
        Events() = delete;
        Events(const Events&) = delete;
        void operator=(Events const&) = delete;
    private:
        friend class Level;
        friend class GLPipeline;
        friend class Actor;

        static void callTick(float deltaTime);
        static void callBegin();
        static void callEnd();

        static void clear();
    };
}