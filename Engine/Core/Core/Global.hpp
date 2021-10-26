// Global.hpp
// Last update 11/10/2021 by Madman10K
#pragma once
#include <Core/ECS.hpp>
#include <Renderer/Window/Window.hpp>
#include <Renderer/UI/UI.hpp>
#include <Assets/AssetManager.hpp>
#include "UUID.hpp"

namespace UVK
{
    struct RendererSettings
    {
        RendererSettings() = default;
        std::string themeLoc;
        bool bVsync = false;
        bool bVsyncImmediate = true;
        uint32_t maxSavedTransactions = 0;

        void saveSettings() const;
    };

    class Level;
    class GameInstance;

    class UVKGlobal
    {
    public:
        UVKGlobal();
        ~UVKGlobal();
        UVKGlobal(const UVKGlobal&) = delete;
        void operator=(UVKGlobal const&) = delete;

        GameInstance* instance = nullptr;
        WindowInternal window;

        bool& getEditor();
        Level* currentLevel = nullptr;
        AssetManager assetManager;

        static void openLevelInternal(UVK::String name, bool bfirst = false);

        std::string levelLocation;
        bool bUsesVulkan{};
    private:
        IDManager idManager;

        RendererSettings rendererSettings;

        std::string levelName;

        FVector4 colour{};
        FVector4 ambientLight{};

        bool bEditor{};
        ECSManager ecs;

        std::vector<InputAction> inputActionList;
        UIInternal ui;

        /**
         * @note Open the documentation for Levels and opening of levels for more info about this function
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
        friend class StateTracker;
        friend class Utility;
        friend class IDManager;
        friend struct MeshComponentRaw;
        friend struct RendererSettings;
    };

    inline UVKGlobal global;
}