#pragma once
#include <Core/ECS.hpp>
#include <Renderer/Window/Window.hpp>
#include <Renderer/UI/UI.hpp>
#include <Assets/AssetManager.hpp>
#include "UUID.hpp"
#include <Core/Locale/Locale.hpp>
#include <Renderer/Utils/RendererUtils.hpp>

namespace UVK
{
    class Level;
    class GameInstance;
    class InternalRendererComponents;
    class LocaleManager;

    class UVK_PUBLIC_API UVKGlobal
    {
    public:
        UVKGlobal() noexcept;
        ~UVKGlobal() noexcept;
        UVKGlobal(const UVKGlobal&) = delete;
        void operator=(UVKGlobal const&) = delete;

        GameInstance* instance = nullptr;
        WindowInternal window;

        bool& getEditor() noexcept;
        Level* currentLevel = nullptr;
        AssetManager assetManager;

        static void openLevelInternal(UVK::String name, bool bfirst = false) noexcept;

        FString levelLocation;
        bool bUsesVulkan{};

        std::function<void(void)> modbegin = [=](){};
        std::function<void(float)> modtick = [=](float){};
        std::function<void(void)> modend = [=](){};

        InternalRendererComponents* renderer = nullptr;
    private:
        IDManager idManager;

        RendererSettings rendererSettings;

        FString levelName;

        FVector4 colour{};
        FVector4 ambientLight{};

        bool bEditor{};
        ECSManager ecs;

        UIInternal ui{};
        LocaleManager localeManager{};

        /**
         * @note Open the documentation for Levels and opening of levels for more info about this function
         */
        void finalizeOpening() noexcept;
        std::vector<InputAction>& getActions() noexcept;

        std::function<void(void)> openFunction = [=](){};

        friend class RendererInternal;
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
        friend class EditorResources;
        friend class StateTracker;
        friend class Utility;
        friend class IDManager;
        friend class VulkanRenderer;
        friend class Events;
        friend class EditorUtilSettings;
        friend class Swapchain;
        friend class Commands;
        friend class InternalRendererComponents;
        friend class Locale;
        friend class VKResources;
        friend class VKDescriptors;
        friend struct MeshComponentRaw;
        friend struct MeshComponent;
        friend struct RendererSettings;
        friend struct InitInfo;
    };

    inline UVKGlobal global;
}
