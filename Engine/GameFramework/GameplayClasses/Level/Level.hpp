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
    class UVK_PUBLIC_API Level
    {
    public:
        Level() = default;

        virtual void tick(float deltaTime) = 0;
        virtual void beginPlay() = 0;
        virtual void endPlay() = 0;
        inline virtual ~Level() noexcept
        {
            delete gameMode;
        }

        /**
         * @brief Saves to a level file with a location
         * @param location the ouput location of the file
         * @param name the name of the level IT IS NOT INCLUDED IN LOCATION AND IS ONLY USED FOR SAVING
         */
        static void save(String location) noexcept;

        /**
         * @brief Opens a level file
         * @param location: file location
         * @note For engine devs: this function works by setting a global function* to point to the generated
         * function below. This function* is called and then reset to an empty function every frame(GLPipeline L95)
         */
        template<typename T>
        static void open(const UVK::FString& location) noexcept
        {
            // Capturing by value, otherwise the function crashes
            global.openFunction = [location]()
            {
                global.currentLevel->endPlay();
                delete global.currentLevel;
                T* lvl = new T();
                global.currentLevel = lvl;
                T::openInternal(location.c_str(), false);
                global.currentLevel->beginPlay();
            };
        }

        template<typename T>
        inline static T* cast(Level* lvl) noexcept
        {
            return static_cast<T*>(lvl);
        }

        GameMode* gameMode = nullptr;

        /**
         * @brief Begin event autohandler handles all events from the GameInstance and GameMode
         */
        void beginAutohandle() const noexcept;

        /**
         * @brief Tick event autohandler handles all events from the GameInstance and GameMode
         */
        void tickAutohandle(float deltaTime) const noexcept;

        /**
         * @brief End event autohandler handles all events from the GameInstance and GameMode
         */
        void endAutohandle() const noexcept;

        static FVector4& getAmbientLighting() noexcept;
        static FVector4& getSceneColour() noexcept;
        static UVK::FString& getLevelName() noexcept;

        static PlayerController* getPlayerController(Level* lvl) noexcept;
        static Pawn* getPawn(Level* lvl) noexcept;
        static GameState* getGameState(Level* lvl) noexcept;
        static PlayerState* getPlayerState(Level* lvl) noexcept;
    private:
        friend class UVKGlobal;

        static void openInternal(String file, bool first = false) noexcept;
        /**
         * @brief Utility function to save an entity
         * @param out a YAML::Emitter reference to the emitter
         * @param act actor to be saved
         */
        static void saveEntity(YAML::Emitter& out, entt::entity act) noexcept;
    };
}