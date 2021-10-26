// Level.hpp
// Last update 27/8/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../GameMode.hpp"
#include "../GameInstance.hpp"
#include <Core/Global.hpp>

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
         * @note For engine devs: this function works by setting a global function* to point to the generated
         * function below. This function* is called and then reset to an empty function every frame(GLPipeline L95)
         */
        template<typename T>
        static void open(const std::string& location) noexcept
        {
            // Capturing by value, otherwise the function crashes
            global.openFunction = [location]()
            {
                global.currentLevel->endPlay();
                delete global.currentLevel;
                T* lvl = new T();
                global.currentLevel = lvl;
                T::openInternal(location.c_str());
                global.currentLevel->beginPlay();
            };
        }

        template<typename T>
        static T* cast(Level* lvl)
        {
            return static_cast<T*>(lvl);
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

        static PlayerController* getPlayerController(Level* lvl);
        static Pawn* getPawn(Level* lvl);
        static GameState* getGameState(Level* lvl);
        static PlayerState* getPlayerState(Level* lvl);
    private:
        friend class UVKGlobal;

        static void openInternal(String file, bool first = false);
        /**
         * @brief Utility function to save an entity
         * @param out a YAML::Emitter reference to the emitter
         * @param act actor to be saved
         */
        static void saveEntity(YAML::Emitter& out, entt::entity act);
    };
}