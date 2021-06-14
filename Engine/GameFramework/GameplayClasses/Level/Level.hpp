// Level.hpp
// Last update 13/6/2021 by Madman10K
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
         * @param file file location
         */
        static void open(String file) noexcept;

        GameInstance* gameInstance = nullptr;
        GameMode* gameMode = nullptr;
    private:


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

        /**
         * @brief Utility function to save an entity
         * @param out a YAML::Emitter reference to the emitter
         * @param act actor to be saved
         */
        static void saveEntity(YAML::Emitter& out, Actor act);
    };
}