// Level.hpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)
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
        virtual void Tick(float DeltaTime) = 0;
        virtual void BeginPlay() = 0;
        virtual void EndPlay() = 0;

        void SaveEntity(YAML::Emitter& out, Actor act);
        void Save(String output, String name);
        void Open(String file);

        void SetGameInstance(GameInstance* instance){ gameInstance = instance;}
        void SetGameMode(GameMode* mode){ gameMode = mode; }
        GameMode& GetGameMode(){ return *gameMode; }
    private:
        GameInstance* gameInstance;
        GameMode* gameMode;
    };
}