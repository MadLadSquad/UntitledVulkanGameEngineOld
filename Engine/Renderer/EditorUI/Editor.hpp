// Editor.hpp
// Last update 17/10/2021 by Madman10K
#pragma once
#include <Renderer/Camera/Camera.hpp>
#include <Renderer/Textures/Texture.hpp>
#include <Renderer/OpenGL/Components/GLFrameBuffer.hpp>
#include <Core/Actor.hpp>
#include <UVKLogImGui.h>

namespace UVK
{
#ifndef PRODUCTION
    /**
     * @brief Controls the whole editor and related operations
     */
    class Editor
    {
    public:
        Editor() = default;
        Editor(const Editor&) = delete;
        void operator=(Editor const&) = delete;
    private:
        friend class GLPipeline;
        friend class EditorModules;
        friend class EditorPawn;
        friend class Utility;
        friend class Renderer;
        friend struct RendererSettings;

        double* getFrameTimeData()
        {
            return frameTimeData;
        }

        void initEditor();
        void runEditor(FVector4& colour, GLFrameBuffer& fb, Camera& camera, UVK::Level* lvl);
        static void beginFrame();
        void destroyContext();

        void setTheme(UVK::String theme)
        {
            colTheme = theme;
        }

        Texture play;
        Texture logoTxt;
        Texture fileTextures[8];

        int entNum = 0;
        int viewportWidth = 0, viewportHeight = 0;

        Actor selectedEntity{};

        struct Booleans
        {
            Booleans()
            {
                bShowOpenLevelWidget = false;
                bShowSaveLevelWidget = false;
                bFinalisedCommand = false;
                bShowCreateFile1 = false;
                bShowAboutUs = false;
                bShowSaveWarning = false;
                bShowHelp = false;
                bDestroyEntity = false;
                bShowFilesystem = true;
                bShowStatistics = false;
                bShowViewport = true;
                bShowDetailsPanel = true;
                bShowTerminalEmulator = true;
                bShowSceneHierarchy = true;
                bShowWorldSettings = true;
                bShowToolbar = true;
                bShowTools = true;
                bShowMemoryEditor = true;
                bShowRemoveFile = false;
                bShowShip = false;
                bShowWindowSettings = false;
                bShowRendererSettings = false;
                bShowKeybindSettings = false;
                bShowThemeSettings = false;
                bShowGameKeybinds = false;
                bShowGameSettings = false;
                bShowDirectSaveWarning = false;
                bShowExitWarning = false;
                bShowGenerateWarning = false;
                bShowDeveloperConsole = true;
                bEditorViewportFocused = false;
                bEditorUsingTextbox = false;
                bRecordingUndoRedoTime = false;
            }
            bool bShowOpenLevelWidget;
            bool bShowSaveLevelWidget;
            bool bFinalisedCommand;
            bool bShowCreateFile1;
            bool bShowAboutUs;
            bool bShowSaveWarning;
            bool bShowHelp;
            bool bDestroyEntity;
            bool bShowFilesystem;
            bool bShowStatistics;
            bool bShowViewport;
            bool bShowDetailsPanel;
            bool bShowTerminalEmulator;
            bool bShowSceneHierarchy;
            bool bShowWorldSettings;
            bool bShowToolbar;
            bool bShowTools;
            bool bShowMemoryEditor;
            bool bShowRemoveFile;
            bool bShowShip;
            bool bShowWindowSettings;
            bool bShowRendererSettings;
            bool bShowKeybindSettings;
            bool bShowThemeSettings;
            bool bShowGameKeybinds;
            bool bShowGameSettings;
            bool bShowDirectSaveWarning;
            bool bShowExitWarning;
            bool bShowGenerateWarning;
            bool bShowDeveloperConsole;
            bool bEditorViewportFocused;
            bool bEditorUsingTextbox;
            bool bRecordingUndoRedoTime;
        } bools = Booleans();
        void displayEditor(FVector4& colour, GLFrameBuffer& fb, Camera& camera, UVK::Level* lvl);

        std::string openLevel;
        std::string location;
        std::string name;
        std::string fileOutLocation;
        std::string entAppend;
        std::string terminalCommand;
        std::string engineVersion;
        std::string projectVersion;
        std::string projectName;
        std::string startupLevel;
        UVK::String colTheme{};

        EditorModuleManager moduleManager;

#ifndef __MINGW32__
        std_filesystem::path pt;
        double frameTimeData[2] = { 0.0, 0.0 };
#endif

        /**
         * @brief Contains strings for the different keys used in editor hints
         * @note Naming conventions are broken here due to the fact that the names should resemble their YAML form
         */
        struct EditorKeys
        {
            std::string editor_level_save;
            std::string editor_level_new;
            std::string editor_level_saveas;
            std::string editor_level_open;
            std::string editor_new_file;
            std::string editor_undo;
            std::string editor_redo;
        };
        UVKLogImGui loggerwidget;
        EditorKeys keys;

        FilesystemWidgetData filesystemWidgetData{};
    };
#else
    class Editor
    {
    public:
        Editor();

        EditorModuleManager moduleManager;
    };
#endif
}
