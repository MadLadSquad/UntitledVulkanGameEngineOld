// ActorManager.hpp
// Last update 5/6/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "ScriptableObject.hpp"

namespace UVK
{
    /**
     * @brief The actor manager is a simple data structure holding a set of actors allowing for native
     * scripting. The only member function called `init` is called when the engine starts up
     */
    class ActorManager
    {
    public:
        ActorManager() = default;

        void init();
        void destroy();
        std::set<ScriptableObject*>& data();
    private:
        std::set<ScriptableObject*> a;
    };
}

inline UVK::ActorManager actorManager;