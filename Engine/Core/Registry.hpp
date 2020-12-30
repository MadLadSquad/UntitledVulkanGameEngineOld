#include "../GameFramework/Components/Components.hpp"

namespace Registry
{
    static std::unordered_map<String, Actor> registry;
    static EntityPool pool;
    static void CreateActor(String name)
    {
        Actor act = pool.create();
        pool.emplace<UVK::CoreComponent>(act, name);

        registry.insert(std::make_pair(name, act));
    }

    template<typename T>
    static auto& GetComponent(Actor act)
    {
        auto& a = pool.get<T>(act);
        return a;
    }


}

/*class Registry
{
public:
    static Registry& Get()
    {
        static Registry instance;
        return instance;
    }
    std::unordered_map<String, Actor> registry;

    void CreateActor(String name)
    {
        Actor act;

        pool.emplace<UVK::CoreComponent>(act);

        registry.insert(std::make_pair(name, act));
    }

    template<typename T>
    auto& GetComponent(Actor act)
    {
        return pool.get<T>(act);
    }


private:

    EntityPool pool;

    Registry() {}
    Registry(const Registry&) = delete;
};
 */