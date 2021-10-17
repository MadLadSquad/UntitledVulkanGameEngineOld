// Editor.hpp
// Last update 28/9/2021 by Madman10K
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

        bool bShowOpenLevelWidget= false;
        bool bShowSaveLevelWidget = false;
        bool bFinalisedCommand = false;
        bool bShowCreateFile1 = false;
        bool bShowAboutUs = false;
        bool bShowSaveWarning = false;
        bool bShowHelp = false;
        bool bDestroyEntity = false;
        bool bShowFilesystem = true;
        bool bShowStatistics = false;
        bool bShowViewport = true;
        bool bShowDetailsPanel = true;
        bool bShowTerminalEmulator = true;
        bool bShowSceneHierarchy = true;
        bool bShowWorldSettings = true;
        bool bShowToolbar = true;
        bool bShowTools = true;
        bool bShowMemoryEditor = true;
        bool bShowRemoveFile = false;
        bool bShowShip = false;
        bool bShowWindowSettings = false;
        bool bShowRendererSettings = false;
        bool bShowKeybindSettings = false;
        bool bShowThemeSettings = false;
        bool bShowGameKeybinds = false;
        bool bShowGameSettings = false;
        bool bShowDirectSaveWarning = false;
        bool bShowExitWarning = false;
        bool bShowGenerateWarning = false;
        bool bShowDeveloperConsole = true;
        bool bEditorViewportFocused = false;
        bool bEditorUsingTextbox = false;

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
