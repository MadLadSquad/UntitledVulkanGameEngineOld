#include "Game.hpp"

namespace UVK
{
    class StartupLevel : public UVK::Level
    {
    public:
        StartupLevel();
        virtual void tick(float deltaTime) override;
        virtual void endPlay() override;
        virtual void beginPlay() override;
    };
}
