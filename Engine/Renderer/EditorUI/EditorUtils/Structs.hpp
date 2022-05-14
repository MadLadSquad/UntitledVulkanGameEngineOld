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
        // Current terminal command
        UVK::FString terminalCommand;
        // Current colour theme location
        UVK::String colTheme{};
        // Current engine version
        UVK::FString engineVersion;
        // Current project version
        UVK::FString projectVersion;
        // Current project name
        UVK::FString projectName;
        // Current project startup level name
        UVK::FString startupLevel;
    };

    /**
     * @brief A lot of booleans that are used for the editor, mostly for windows
     */
    struct EditorBooleans
    {
        EditorBooleans() = default;

        // Shows the open level window
        bool bShowOpenLevelWidget = false;
        // Shows the save level window
        bool bShowSaveLevelWidget = false;

        // ?????????
        bool bFinalisedCommand = false;

        // Shows the create file window
        bool bShowCreateFile1 = false;
        // Shows the about us window
        bool bShowAboutUs = false;
        // Shows the save warning popup
        bool bShowSaveWarning = false;
        // Shows the help window
        bool bShowHelp = false;
        // Shows the "destroy entity" warning popup
        bool bDestroyEntity = false;
        // Shows the filesystem window
        bool bShowFilesystem = true;
        // Shows the statistics window
        bool bShowStatistics = false;
        // Shows the viewport window
        bool bShowViewport = true;
        // Shows the details panel window
        bool bShowDetailsPanel = true;
        // Shows the TerminalEmulator window
        bool bShowTerminalEmulator = true;
        // Shows the Scene hierarchy window
        bool bShowSceneHierarchy = true;
        // Shows the world settings window
        bool bShowWorldSettings = true;
        // Shows the top toolbar window
        bool bShowToolbar = true;
        // Shows the tools window
        bool bShowTools = true;
        // Shows the memory editor window
        bool bShowMemoryEditor = true;
        // Shows the remove file window
        bool bShowRemoveFile = false;
        // Shows the ship to production window
        bool bShowShip = false;
        // Shows the window settings editor window
        bool bShowWindowSettings = false;
        // Shows the renderer settings editor window
        bool bShowRendererSettings = false;
        // Shows the keybind settings editor window
        bool bShowKeybindSettings = false;
        // Shows the theme settings editor window
        bool bShowThemeSettings = false;
        // Shows the game keybings editor window
        bool bShowGameKeybinds = false;
        // Shows the game settings editor window
        bool bShowGameSettings = false;
        // Shows the direct save warning popup
        bool bShowDirectSaveWarning = false;
        // Shows the exit warning popup
        bool bShowExitWarning = false;
        // Shows the "regenerate warning" popup
        bool bShowGenerateWarning = false;
        // Shows the developer console window
        bool bShowDeveloperConsole = true;
        // A boolean to track if the viewport window is focused
        bool bEditorViewportFocused = false;
        // A boolean to check if the user is currently focused on a textbox
        bool bEditorUsingTextbox = false;
        // Shows the ditor settigns editor window
        bool bShowEditorSettings = false;
    };

    /**
     * @brief All the textures the editor needs
     * @var play - Play button on the top bar
     * @var restart - Restart button after the play button has been pressed
     * @var stop - Stop button after the play button has been pressed
     * @var logoTxt - The texture for our brand logo
     * @var fileTextures - An array of textures where every index specifies a texture, indexes correspond to values in the EditorTextures child enum
     */
    struct EditorTextures
    {
        /**
         * @brief an enum that contains all indexes of the different filesystem thumbnails
         */
        enum FilesystemIconIndices
        {
            FS_ICON_AUDIO = 0,
            FS_ICON_IMAGE = 1,
            FS_ICON_VIDEO = 2,
            FS_ICON_FOLDER = 3,
            FS_ICON_FONT = 4,
            FS_ICON_MODEL = 5,
            FS_ICON_UNKNOWN = 6,
            FS_ICON_CODE = 7,
            FS_ICON_CLOSE = 8,
        };

        Texture play;
        Texture restart;
        Texture stop;
        Texture logoTxt;
        Texture fileTextures[9];
    };

    /**
     * @brief A struct containing all settings for the editor
     * @struct FilesystemWidgetData - A struct containing settings for the Filesystem widget
     * @var maxSavedTransactions - The number of maximum transactions before we start to override old ones
     * @var editorLayoutLocation - The file location of the editor layout
     * @var fsdata - An instance of the "FilesystemWidgetData" struct
     */
    struct EditorSettings
    {
        /**
         * @brief A struct containing settings for the Filesystem widget
         * @var padding - A float specifying the amount of padding between filesystem elements
         * @var imageSize - The size of the thumbnail/preview image and button on the filesystem
         * @var maxFileNum - The maximum number of files before we start to not show previews
         * @var bUsePreviews - Should we use previews by default
         */
        struct FilesystemWidgetData
        {
            float padding = 20.0f;
            float imageSize = 50.0f;
            uint32_t maxFileNum = 64;
            bool bUsePreviews = false;
        };
        void writeToFile(Editor& editor) const noexcept;

        uint32_t maxSavedTransactions = 100;
        UVK::FString editorLayoutLocation = "../Config/Engine/FallbackLayout";
        FilesystemWidgetData fsdata;
    };
#endif
}
