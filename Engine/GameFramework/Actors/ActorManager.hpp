// ActorManager.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <Core/STL.hpp>

namespace UVK
{
    class ScriptableObject;

    /**
     * @brief The actor manager is a simple data structure holding a set of actors allowing for native
     * scripting. The only member function called `init` is called when the engine starts up
     */
    class UVK_PUBLIC_API ActorManager
    {
    public:
        ActorManager() = default;
        ~ActorManager();
    private:
        friend class UVKGlobal;
        friend class GameInstance;
        friend class Actor;
        friend class Events;

        std::vector<ScriptableObject*>& data();

        void init();
        void destroy();
        std::vector<ScriptableObject*> a;
    };
}