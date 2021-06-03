// Events.hpp
// Last update 3/6/2021 by Madman10K
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
        void callTick(float deltaTime)
        {
            for (auto& a : objList)
            {
                a->tick(deltaTime);
            }
        }

        void callBegin()
        {
            for (auto& a : objList)
            {
                a->beginPlay();
            }
        }

        void callEnd()
        {
            for (auto& a : objList)
            {
                a->endPlay();
            }
        }

        [[maybe_unused]] void createObj(ScriptableObject* sco)
        {
            objList.push_back(sco);
        }
    private:
        std::vector<ScriptableObject*> objList;
    };


}

inline UVK::Events events;