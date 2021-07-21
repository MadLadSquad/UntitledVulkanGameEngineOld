// Level.hpp
// Last update 21/7/2021 by Madman10K
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
        Level() = default;

        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;
        virtual ~Level()
        {
            delete gameMode;
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
         * @note detailed description of this function and the whole Level opening system
         * can be found in Core/Core/Utility.hpp
         */
        template<typename T>
        static void open(String location) noexcept
        {
            // Capturing by value, otherwise the function crashes
            Internal::openFunction = [location]()
            {
                T* lvl = new T();
                Internal::currentLevel = lvl;
                T::openInternal(location);
                Internal::currentLevel->beginPlay();
            };

            Internal::openConfirmation = true;
        }

        GameMode* gameMode = nullptr;

        /**
         * @brief Begin event autohandler handles all events from the GameInstance and GameMode
         */
        void beginAutohandle() const;

        /**
         * @brief Tick event autohandler handles all events from the GameInstance and GameMode
         */
        void tickAutohandle(float deltaTime) const;

        /**
         * @brief End event autohandler handles all events from the GameInstance and GameMode
         */
        void endAutohandle() const;



        static FVector4& getAmbientLighting();
        static FVector4& getSceneColour();
        static std::string& getLevelName();
    private:
        friend class UVKGlobal;

        static void openInternal(String file);
        /**
         * @brief Utility function to save an entity
         * @param out a YAML::Emitter reference to the emitter
         * @param act actor to be saved
         */
        static void saveEntity(YAML::Emitter& out, entt::entity act);

    };
}