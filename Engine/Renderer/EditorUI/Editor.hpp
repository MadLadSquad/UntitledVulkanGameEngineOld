#pragma once
#include <Renderer/Camera/Camera.hpp>
#include <Renderer/Textures/Texture.hpp>
#include <Renderer/OpenGL/Components/GLFrameBuffer.hpp>
#include <Core/Actor.hpp>

#include <UVKLogImGui.h>
#include <Renderer/EditorUI/EditorUtils/Structs.hpp>

namespace UVK
{
#ifndef PRODUCTION
    /**
     * @brief Controls the whole editor and related operations
     */
    class UVK_PUBLIC_API Editor
    {
    public:
        Editor() = default;
        Editor(const Editor&) = delete;
        void operator=(Editor const&) = delete;
    private:
        friend class VulkanRenderer;
        friend class GLPipeline;
        friend class EditorModules;
        friend class EditorPawn;
        friend class Utility;
        friend class Renderer;
        friend class EditorPointer;
        friend class Level;
        friend class EditorResources;
        friend class EditorGUIUtils;
        friend class StateTracker;
        friend class EditorSettings;
        friend class RendererSettingsWidget;
        friend class EditorSettingsWidget;
        friend class EditorUtilSettings;
        friend struct RendererSettings;

        inline double* getFrameTimeData() noexcept
        {
            return frameTimeData;
        }

        void initEditor() noexcept;
        void runEditor(FVector4& colour, Camera& camera, UVK::Level* lvl, const float& deltaTime) noexcept;
        void displayEditor(FVector4& colour, Camera& camera, UVK::Level* lvl, const float& deltaTime) noexcept;
        static void beginFrame() noexcept;
        void destroyContext() noexcept;

        inline void setTheme(UVK::String theme) noexcept
        {
            strings.colTheme = theme;
        }

        int entNum = 0;
        int viewportWidth = 0, viewportHeight = 0;

        Actor selectedEntity{};

        double accumulateUndoRedo = 0;

        EditorTextures textures;
        EditorBooleans bools;
        EditorStrings strings;
        EditorModuleManager moduleManager;

#ifndef __MINGW32__
        std_filesystem::path pt;
        double frameTimeData[2] = { 0.0, 0.0 };
#endif
        UVKLog::ImGuiConsole loggerwidget;
        EditorKeys keys;

        EditorSettings settings;
        std::vector<EditorFolder> currentLevelFolders;
    };
    class GameInstance;

    struct EditorPointer
    {
    public:
        EditorPointer() noexcept;
        Editor* data() noexcept;
        Texture* fsicons() noexcept;
    private:
        Editor* ptr = nullptr;
    };
#else
    class Editor
    {
    public:
        Editor() noexcept;
        FilesystemWidgetData filesystemWidgetData{};
        EditorModuleManager moduleManager;
    };
#endif
}
