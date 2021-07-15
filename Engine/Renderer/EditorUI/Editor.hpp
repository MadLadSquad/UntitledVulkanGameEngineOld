// Editor.hpp
// Last update 6/7/2021 by Madman10K
#pragma once
#include <iostream>
#include <utility>
#include <Core/Actor.hpp>
#include <Core.hpp>
#include "Widgets/EditorViewport.hpp"
#include "../Textures/Texture.hpp"
#include <Audio/Audio.hpp>


namespace UVK
{
    //class Level;

    /**
     * @brief Controls the whole editor and related operations
     */
    class Editor
    {
    public:
        Editor() = default;
    private:
        friend class GLPipeline;

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
        Texture insert;

        std::array<Texture, 8> fileTextures;

        int entNum = 0;
        int viewportWidth = 0, viewportHeight = 0;
        uint8_t selectedFile = 0;

        Actor selectedEntity;

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

        void displayEditor(FVector4& colour, GLFrameBuffer& fb, Camera& camera, UVK::Level* lvl);

        std::string levelName;
        std::string openLevel;
        std::string location;
        std::string name;
        std::string fileOutLocation;
        std::string entAppend;
        std::string terminalCommand;
        std::string engineVersion;
        std::string projectVersion;
        std::string projectName;
        UVK::String colTheme;
        std::string cpFileLoc;

        double frameTimeData[2] = { 0.0, 0.0 };
#ifndef __MINGW32__
        std_filesystem::path pt;
#endif
    };
}
