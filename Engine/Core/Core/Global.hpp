// Global.hpp
// Last update 18/7/2021 by Madman10K
#pragma once
#include <Core/ECS.hpp>
#include <Core.hpp>
#include <Renderer/Window/Window.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>
#include <GameFramework/Actors/ActorManager.hpp>
#include <Renderer/UI/UI.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <Events/Events.hpp>

namespace UVK
{
    struct RendererSettings
    {
        RendererSettings() = default;
        std::string themeLoc;
        bool bVulkan = false;

        void saveSettings() const;
    };

    class UVKGlobal
    {
    public:
        UVKGlobal();
        ~UVKGlobal();

        GameInstance* instance{};
        WindowInternal window;

        bool& getEditor();
        Level* currentLevel = nullptr;
    private:
        RendererSettings rendererSettings;

        std::string levelName;
        std::string levelLocation;

        FVector4 colour{};
        FVector4 ambientLight{};

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
        friend struct MeshComponentRaw;

        bool bEditor{};
        bool bUsesVulkan{};
        ECSManager ecs;

        UVK::Events events;
        UVK::ActorManager actorManager;
        std::vector<InputAction> inputActionList;
        UIInternal ui;

        void finalizeOpening();
        std::vector<InputAction>& getActions();
    };

    inline UVKGlobal global;

    class InputActions
    {
    public:
        static std::vector<InputAction>& getActions();
    };

    class Math
    {
    public:
        static void translate(glm::mat4& mat, FVector vt);
        static void rotate(glm::mat4& mat, FVector vt);
        static void scale(glm::mat4& mat, FVector vt);
    };
}