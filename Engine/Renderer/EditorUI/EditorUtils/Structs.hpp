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
        ~EditorFolder() noexcept
        {
            name.clear();
            contents.clear();
            bValid = false;
        }
        UVK::FString name = "NewFolder";
        bool bValid = true; // Saving if a folder is valid for later
        std::vector<UVK::Actor> contents;
    };

    /**
     * @brief Contains strings for the different keys used in editor hints
     * @note Naming conventions are broken here due to the fact that the names should resemble their YAML form
     */
    struct EditorKeys
    {
        UVK::FString editor_level_save;
        UVK::FString editor_level_new;
        UVK::FString editor_level_saveas;
        UVK::FString editor_level_open;
        UVK::FString editor_new_file;
        UVK::FString editor_undo;
        UVK::FString editor_redo;
    };

    /**
     * @brief A bunch of strings used for the editor
     */
    struct EditorStrings
    {
        UVK::FString openLevel;
        UVK::FString location;
        UVK::FString name;
        UVK::FString fileOutLocation;
        UVK::FString terminalCommand;
        UVK::String colTheme{};
        UVK::FString engineVersion;
        UVK::FString projectVersion;
        UVK::FString projectName;
        UVK::FString startupLevel;
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
        void writeToFile(Editor& editor) const noexcept;

        uint32_t maxSavedTransactions = 100;
        UVK::FString editorLayoutLocation = "../Config/Engine/FallbackLayout";
        FilesystemWidgetData fsdata;
    };
#endif
}
