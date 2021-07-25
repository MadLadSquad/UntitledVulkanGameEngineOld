// Actor.hpp
// Last update 25/7/2021 by Madman10K
#include <Core/Global.hpp>
#include <GameFramework/Actors/ScriptableObject.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>


namespace UVK
{
    class Actor
    {
    public:
        Actor() = default;

        Actor(const std::string &nameN, uint64_t idN, const std::string &devNameN, bool bCreatedByLevel = false);

        void create(const std::string &nameN, uint64_t idN, const std::string &devNameN, bool bCreatedByLevel);

        template<typename T>
        auto& get()
        {
            return global.ecs.data().get<T>(entity);
        }

        template<typename T>
        auto& add()
        {
            return global.ecs.data().emplace_or_replace<T>(entity);
        }

        template<typename T>
        void remove()
        {
            global.ecs.data().remove_if_exists<T>(entity);
        }

        template<typename T>
        bool has()
        {
            return global.ecs.data().has<T>(entity);
        }

        void destroy();
        entt::entity& data();
    private:
        entt::entity entity;
    };
}