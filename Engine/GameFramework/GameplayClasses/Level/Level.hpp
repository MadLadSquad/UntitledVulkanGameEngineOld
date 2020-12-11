// Level.hpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)
#include <Core.hpp>
#include "../GameMode.hpp"
#include "../GameInstance.hpp"
#include "../../Core/Assets/Asset.hpp"


namespace UVK
{
    class UVK_API Level
    {
    public:
        void Serialise(String output);
        void Deserialise(AssetReference assetRef);

        void SetGameInstance(GameInstance* instance)
        {
            gameInstance = instance;
        }

        void SetGameMode(GameMode* mode)
        {
            gameMode = mode;
        }

        GameMode& GetGameMode()
        {
            return *gameMode;
        }

    private:
        GameInstance* gameInstance;
        GameMode* gameMode;
    };
}