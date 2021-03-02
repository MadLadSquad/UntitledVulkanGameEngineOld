// Level.hpp
// Last update 2/24/2021 by Madman10K
#include <Core.hpp>
#include "../GameMode.hpp"
#include "../GameInstance.hpp"
#include "../../Components/Components.hpp"
#include "Engine/Core/Core/Registry.hpp"

namespace UVK
{

    class UVK_API Level
    {
    public:
        //Level(const char* name) { open(name); }
        Level() = default;

        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;

        static void saveEntity(YAML::Emitter& out, Actor act);
        static void save(String location, String name);
        static void open(String file) noexcept;

        GameInstance* gameInstance = nullptr;
        GameMode* gameMode = nullptr;

        void beginAutohandle() const
        {
            gameInstance->beginPlay();
            gameMode->beginPlay();
        }

        void tickAutohandle(float deltaTime) const
        {
            gameInstance->tick(deltaTime);
            gameMode->tick(deltaTime);
        }

        void endAutohandle() const
        {
            gameInstance->endPlay();
            gameMode->endPlay();
        }
    private:

    };
}