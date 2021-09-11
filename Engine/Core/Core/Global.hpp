// Global.hpp
// Last update 1/8/2021 by Madman10K
#pragma once
#include <Core/ECS.hpp>
#include <Core.hpp>
#include <Renderer/Window/Window.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>
#include <GameFramework/Actors/ActorManager.hpp>
#include <Renderer/UI/UI.hpp>
#include <Events/Events.hpp>
#include <Assets/AssetManager.hpp>

namespace UVK
{
    struct RendererSettings
    {
        RendererSettings() = default;
        std::string themeLoc;
        bool bVsync = false;
        bool bVsyncImmediate = true;

        void saveSettings() const;
    };

    class Level;

    class UVKGlobal
    {
    public:
        UVKGlobal();
        ~UVKGlobal();
        UVKGlobal(const UVKGlobal&) = delete;
        void operator=(UVKGlobal const&) = delete;

        GameInstance* instance{};
        WindowInternal window;

        bool& getEditor();
        Level* currentLevel = nullptr;
        AssetManager assetManager;

        static void openLevelInternal(UVK::String name);

        std::string levelLocation;
        bool bUsesVulkan{};
    private:
        RendererSettings rendererSettings;

        std::string levelName;

        FVector4 colour{};
        FVector4 ambientLight{};

        bool bEditor{};
        ECSManager ecs;

        std::vector<InputAction> inputActionList;
        UIInternal ui;

        /**
         * @note detailed description of this function and the whole Level opening system
         * can be found in Core/Core/Utility.hpp
         */
        void finalizeOpening();
        std::vector<InputAction>& getActions();

        std::function<void(void)> openFunction = [=](){};

        friend class Renderer;
        friend class Camera;
        friend class Editor;
        friend class GLPipeline;
        friend class GLEntityManager;
        friend class ECS;
        friend class WindowInternal;
        friend class Input;
        friend class Actor;
        friend class Level;
        friend class UI;
        friend class UIInternal;
        friend class InputActions;
        friend class Math;
        friend class SettingsManager;
        friend class GameInstance;
        friend class Assets;
        friend struct MeshComponentRaw;
        friend struct RendererSettings;
    };

    inline UVKGlobal global;

    class Math
    {
    public:
        static void translate(glm::mat4& mat, FVector vt);
        static void rotate(glm::mat4& mat, FVector vt);
        static void scale(glm::mat4& mat, FVector vt);
    };
}