// Editor.hpp
// Last update 18/2/2022 by Madman10K
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

        double* getFrameTimeData()
        {
            return frameTimeData;
        }

        void initEditor();
        void runEditor(FVector4& colour, GLFrameBuffer& fb, Camera& camera, UVK::Level* lvl, const float& deltaTime);
        void displayEditor(FVector4& colour, GLFrameBuffer& fb, Camera& camera, UVK::Level* lvl, const float& deltaTime);
        static void beginFrame();
        void destroyContext();

        void setTheme(UVK::String theme)
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
        UVKLogImGui loggerwidget;
        EditorKeys keys;

        EditorSettings settings;
        std::vector<EditorFolder> currentLevelFolders;
    };
    class GameInstance;

    struct EditorPointer
    {
    public:
        EditorPointer();
        Editor* data();
        Texture* fsicons();
    private:
        Editor* ptr = nullptr;
    };
#else
    class Editor
    {
    public:
        Editor();
        FilesystemWidgetData filesystemWidgetData{};
        EditorModuleManager moduleManager;
    };
#endif
}
