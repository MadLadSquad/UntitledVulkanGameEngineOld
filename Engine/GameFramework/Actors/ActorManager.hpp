// ActorManager.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    class ScriptableObject;

    /**
     * @brief The actor manager is a simple data structure holding a set of actors allowing for native
     * scripting. The only member function called `init` is called when the engine starts up
     */
    class ActorManager
    {
    public:
        ActorManager() = default;

        std::set<ScriptableObject*>& data();
    private:
        friend class UVKGlobal;
        void init();
        void destroy();
        std::set<ScriptableObject*> a;
    };
}