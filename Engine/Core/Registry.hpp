// Registry.hpp
// Last update 1/10/2021 by Madman10K
#include "../GameFramework/Components/Components.hpp"

inline EntityPool pool;
inline uint64_t id = 0;

class Registry
{
public:
    template<typename T>
    auto& addComponent(Actor& act)
    {
        return pool.emplace<T>(act);
    }

    Actor& createActor(std::string name)
    {
        Actor act = pool.create();

        auto& a = addComponent<UVK::CoreComponent>(act);
        a.name = name;
        a.id = id;

        id = id++;

        return act;
    }

    template<typename T>
    auto& getComponent(Actor& act)
    {
        return pool.get<T>(act);
    }

    template<typename T>
    bool hasComponent(Actor& act)
    {
        return pool.has<T>(act);
    }

    template<typename T>
    void removeComponent(Actor& act)
    {
        pool.remove<T>(act);
    }

    void destroyActor(Actor& act)
    {
        pool.destroy(act);
    }

    Actor& searchByID(uint64_t idNum)
    {
        /*
        pool.each([&](Actor act)
        {
            if (pool.has<UVK::CoreComponent>(act))
            {
                auto& a = pool.get<UVK::CoreComponent>(act);

                if (a.id == idNum)
                {
                    return act;
                }
            }
        });
         */
    };

    Actor& searchByName(std::string name)
    {
        /*pool.each([&](Actor& act)
        {
            if (pool.has<UVK::CoreComponent>(act))
            {
                auto& a = pool.get<UVK::CoreComponent>(act);

                if (a.name == name)
                {
                    return act;
                }
            }
        });
         */
    };

    template<typename T>
    std::vector<Actor*> getAllWithComponent()
    {
        /*std::vector<Actor*> arr;
        pool.each([&](Actor& act)
        {
            if (pool.has<T>(act))
            {
                arr.push_back(&act);
            }
        });

        return arr;
         */
    };

};

inline Registry registry;