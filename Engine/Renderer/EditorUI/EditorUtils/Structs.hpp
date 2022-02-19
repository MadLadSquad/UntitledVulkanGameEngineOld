// Structs.hpp
// Last update 18/2/2022 by Madman10K
#pragma once
#include <vector>
#include <iostream>
#include "Renderer/Textures/Texture.hpp"
#include "Core/Actor.hpp"

namespace UVK
{
#ifndef PRODUCTION
    class Editor;

    struct EditorFolder
    {
        ~EditorFolder()
        {
            name.clear();
            contents.clear();
            bValid = false;
        }
        std::string name = "NewFolder";
        bool bValid = true; // Saving if a folder is valid for later
        std::vector<UVK::Actor> contents;
    };

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

    /**
     * @brief A bunch of strings used for the editor
     */
    struct EditorStrings
    {
        std::string openLevel;
        std::string location;
        std::string name;
        std::string fileOutLocation;
        std::string terminalCommand;
        UVK::String colTheme{};
        std::string engineVersion;
        std::string projectVersion;
        std::string projectName;
        std::string startupLevel;
    };

    /**
     * @brief A lot of booleans that are used for the editor, mostly for windows
     */
    struct EditorBooleans
    {
        EditorBooleans() = default;

        bool bShowOpenLevelWidget = false;
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
        bool bShowEditorSettings = false;
    };

    /**
     * @brief All the textures the editor needs
     */
    struct EditorTextures
    {
        Texture play;
        Texture restart;
        Texture stop;
        Texture logoTxt;
        Texture fileTextures[9];
    };

    struct EditorSettings
    {
        void writeToFile(Editor& editor) const;

        uint32_t maxSavedTransactions = 100;
        std::string editorLayoutLocation = "../Engine/FallbackLayout";
        FilesystemWidgetData fsdata;
    };
#endif
}
