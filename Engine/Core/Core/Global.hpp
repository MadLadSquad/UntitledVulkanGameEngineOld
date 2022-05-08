#pragma once
#include <Core/ECS.hpp>
#include <Renderer/Window/Window.hpp>
#include <Renderer/UI/UI.hpp>
#include <Assets/AssetManager.hpp>
#include "UUID.hpp"
#include <Core/Locale/Locale.hpp>

namespace UVK
{
    struct UVK_PUBLIC_API RendererSettings
    {
        RendererSettings() = default;
        FString themeLoc;
        bool bVsync = false;
        bool bVsyncImmediate = true;
        uint32_t samples = VK_SAMPLE_COUNT_1_BIT;
        bool sampleRateShading = false;
        float sampleRateShadingMult = 0.25f;

        void saveSettings() const noexcept;
    };

    struct UVK_PUBLIC_API ShaderConstantBase
    {
        glm::mat4 view;
        glm::mat4 projection;
    };

    struct UVK_PUBLIC_API ShaderPushConstantBase
    {
        glm::mat4 model;
    };

    // A struct of values that will be constant for all shaders, they can still be changed from frame to frame but will not be different for every shader that uses them
    struct UVK_PUBLIC_API ShaderConstantStruct
    {
        ShaderConstantBase* data = nullptr;
        size_t size = 0;
    };

    // A struct of mutable values of bigger size than 128bits
    struct UVK_PUBLIC_API ShaderMutableStruct
    {
        void* data = nullptr;
        size_t size = 0;

        std::function<void(void*)> updateDynamicUniformBufferCallback = [](void*) {};
    };

    // A struct of mutable values of max size of 128 bits, 64bits occupied by the model struct
    struct UVK_PUBLIC_API ShaderPushConstant
    {
        ShaderPushConstantBase* data = nullptr;
        uint8_t size = 0;
    };

    // The init info struct defines multiple types that can be used to set up certain one time settings
    struct UVK_PUBLIC_API InitInfo
    {
    public:
        ShaderConstantStruct shaderConstantStruct = { &fallbackShaderConstant, sizeof(ShaderConstantBase) };
        ShaderMutableStruct shaderMutableStruct{};
        ShaderPushConstant shaderPushConstant = { &fallbackShaderPushConstant, sizeof(ShaderPushConstantBase) };
    private:
        ShaderConstantBase fallbackShaderConstant{};
        ShaderPushConstantBase fallbackShaderPushConstant{};
    };

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
        InitInfo* initInfo;
        IDManager idManager;

        RendererSettings rendererSettings;

        FString levelName;

        FVector4 colour{};
        FVector4 ambientLight{};

        bool bEditor{};
        ECSManager ecs;

        std::vector<InputAction> inputActionList{};
        UIInternal ui{};
        LocaleManager localeManager{};

        /**
         * @note Open the documentation for Levels and opening of levels for more info about this function
         */
        void finalizeOpening() noexcept;
        std::vector<InputAction>& getActions() noexcept;

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
        friend struct RendererSettings;
        friend struct InitInfo;
    };

    inline UVKGlobal global;
}