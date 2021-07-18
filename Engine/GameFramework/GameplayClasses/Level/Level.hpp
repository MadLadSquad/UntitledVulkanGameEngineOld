// Level.hpp
// Last update 18/7/2021 by Madman10K
#include <Core.hpp>
#include "../GameMode.hpp"
#include "../GameInstance.hpp"

namespace UVK
{
    /**
     * @brief A level class can have it's own scripted events but it has the functionality of opening and saving level
     * files
     */
    class Level
    {
    public:
        //Level(const char* name) { open(name); }
        Level() = default;

        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;
        virtual ~Level()
        {
            delete gameMode;
            delete gameInstance;
        }

        /**
         * @brief Saves to a level file with a location
         * @param location the ouput location of the file
         * @param name the name of the level IT IS NOT INCLUDED IN LOCATION AND IS ONLY USED FOR SAVING
         */
        static void save(String location);

        /**
         * @brief Opens a level file
         * @param location: file location
         */
        template<typename T>
        static void open(String location) noexcept
        {
            Internal::openFunction = [=]()
            {
                const char* loc = location;
                T* lvl = new T();
                Internal::currentLevel = lvl;
                T::openInternal(loc);
                Internal::currentLevel->beginPlay();
            };

            Internal::openConfirmation = true;
        }

        GameInstance* gameInstance = nullptr;
        GameMode* gameMode = nullptr;

        /**
         * @brief Begin event autohandler handles all events from the GameInstance and GameMode
         */
        void beginAutohandle() const
        {
            gameInstance->beginPlay();
            gameMode->beginPlay();
        }
        /**
         * @brief Tick event autohandler handles all events from the GameInstance and GameMode
         */
        void tickAutohandle(float deltaTime) const
        {
            gameInstance->tick(deltaTime);
            gameMode->tick(deltaTime);
        }

        /**
         * @brief End event autohandler handles all events from the GameInstance and GameMode
         */
        void endAutohandle() const
        {
            gameInstance->endPlay();
            gameMode->endPlay();
        }

        static void openInternal(String file);

        static FVector4& getAmbientLighting();
        static FVector4& getSceneColour();
        static std::string& getLevelName();
    private:
        friend struct UVKGlobal;

        /**
         * @brief Utility function to save an entity
         * @param out a YAML::Emitter reference to the emitter
         * @param act actor to be saved
         */
        static void saveEntity(YAML::Emitter& out, entt::entity act);

    };
}