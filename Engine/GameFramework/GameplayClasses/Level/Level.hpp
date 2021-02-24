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

        void saveEntity(YAML::Emitter& out, Actor act);
        void save(String location, String name);
        void open(String file) noexcept;

        GameInstance* gameInstance;
        GameMode* gameMode;

        void beginAutohandle()
        {
            gameInstance->beginPlay();
            gameMode->beginPlay();
        }

        void tickAutohandle(float deltaTime)
        {
            gameInstance->tick(deltaTime);
            gameMode->tick(deltaTime);
        }

        void endAutohandle()
        {
            gameInstance->endPlay();
            gameMode->endPlay();
        }
    private:

    };
}