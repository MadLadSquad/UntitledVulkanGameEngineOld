// Level.hpp
// Last update 1/10/2021 by Madman10K
#include <Core.hpp>
#include "../GameMode.hpp"
#include "../GameInstance.hpp"
#include "../../Components/Components.hpp"
#include "../../../Core/Registry.hpp"

namespace UVK
{

    class UVK_API Level
    {
    public:
        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;

        void saveEntity(YAML::Emitter& out, Actor act);
        void save(String output, String name);
        void open(String file);

        void setGameInstance(GameInstance* instance){ gameInstance = instance;}
        void setGameMode(GameMode* mode){ gameMode = mode; }
        GameMode& getGameMode(){ return *gameMode; }
    private:
        GameInstance* gameInstance;
        GameMode* gameMode;
    };
}