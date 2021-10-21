// Editor.cpp
// Last update 17/10/2021 by Madman10K
#include "Editor.hpp"
#ifndef PRODUCTION
#include "Widgets/SceneHierarchy.hpp"
#include "Widgets/DetailsPanel.hpp"
#include "Widgets/SaveLevel.hpp"
#include "Widgets/TopToolbar.hpp"
#include "Widgets/TerminalEmulator.hpp"
#include "Style/Theme.hpp"
#include "Widgets/Filesystem.hpp"
#include <imguiex/imguizmo/ImGuizmo.h>
#include "Widgets/Statistics.hpp"
#include "Widgets/WorldSettings.hpp"
#include "Widgets/MemoryEditor.hpp"
#include "Widgets/CreateFile.hpp"
#include "Widgets/OpenLevelWidget.hpp"
#include "Widgets/About.hpp"
#include "Widgets/Settings.hpp"
#include "Widgets/NewLevel.hpp"
#include "Widgets/Help.hpp"
#include "Widgets/RemoveFile.hpp"
#include "Widgets/Ship.hpp"
#include "Widgets/Warnings.hpp"
#include "Widgets/Tools.hpp"
#include "Widgets/EditorViewport.hpp"
#include <Engine/Core/Core/Global.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <imgui_impl_vulkan.h>

void UVK::Editor::initEditor()
{
    global.instance->editor = this;
    UVK::Renderer::loadFilesystemSettings();

    auto bindText = Utility::keyToText(Input::getAction("editor-bind-modifier").keyCode, false);
    auto shiftText = Utility::keyToText(Input::getAction("editor-shift").keyCode, false);

    keys = EditorKeys
    {
        .editor_level_save = bindText + "+" + Utility::keyToText(Input::getAction("editor-level-save").keyCode, false),
        .editor_level_new = bindText + "+" + Utility::keyToText(Input::getAction("editor-level-new").keyCode, false),
        .editor_level_saveas = bindText + "+" + shiftText + "+" + Utility::keyToText(Input::getAction("editor-level-saveas").keyCode, false),
        .editor_level_open = bindText + "+" + Utility::keyToText(Input::getAction("editor-level-open").keyCode, false),
        .editor_new_file = bindText + "+" + shiftText + "+" + Utility::keyToText(Input::getAction("editor-new-file").keyCode, false),
        .editor_undo = bindText + "+" + Utility::keyToText(Input::getAction("editor-undo").keyCode, false),
        .editor_redo = bindText + "+" + Utility::keyToText(Input::getAction("editor-redo").keyCode, false),
    };

    Timer tm;
    tm.startRecording();
#ifndef __MINGW32__
    pt = "../Content/";
#endif
    YAML::Node file;
    try
    {
        file = YAML::LoadFile("../uvproj.yaml");
    }
    catch (YAML::BadFile&)
    {
        logger.consoleLog("Could not find uvproj.yaml file", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    if (file["engine-version"] && file["name"] && file["version"] && file["startup-level"])
    {
        engineVersion = file["engine-version"].as<std::string>();
        projectVersion = file["version"].as<std::string>();
        projectName = file["name"].as<std::string>();
        startupLevel = file["startup-level"].as<std::string>();
    }
#ifndef __MINGW32__

    play = Texture(static_cast<std::string>(pt.string() + "Engine/play.png"));
    play.loadImgui();

    logoTxt = Texture(static_cast<std::string>(pt.string() + "Engine/logo.png"));
    logoTxt.loadImgui();

    fileTextures[FS_ICON_AUDIO] = Texture(static_cast<std::string>(pt.string() + "Engine/audio.png"));
    fileTextures[FS_ICON_AUDIO].loadImgui();

    fileTextures[FS_ICON_IMAGE] = Texture(static_cast<std::string>(pt.string() + "Engine/image.png"));
    fileTextures[FS_ICON_IMAGE].loadImgui();

    fileTextures[FS_ICON_VIDEO] = Texture(static_cast<std::string>(pt.string() + "Engine/video.png"));
    fileTextures[FS_ICON_VIDEO].loadImgui();

    fileTextures[FS_ICON_FOLDER] = Texture(static_cast<std::string>(pt.string() + "Engine/folder.png"));
    fileTextures[FS_ICON_FOLDER].loadImgui();

    fileTextures[FS_ICON_FONT] = Texture(static_cast<std::string>(pt.string() + "Engine/font.png"));
    fileTextures[FS_ICON_FONT].loadImgui();

    fileTextures[FS_ICON_MODEL] = Texture(static_cast<std::string>(pt.string() + "Engine/obj.png"));
    fileTextures[FS_ICON_MODEL].loadImgui();

    fileTextures[FS_ICON_UNKNOWN] = Texture(static_cast<std::string>(pt.string() + "Engine/unknown.png"));
    fileTextures[FS_ICON_UNKNOWN].loadImgui();

    fileTextures[FS_ICON_CODE] = Texture(static_cast<std::string>(pt.string() + "Engine/code.png"));
    fileTextures[FS_ICON_CODE].loadImgui();
#else
    play = Texture(static_cast<std::string>("../Content/Engine/play.png"));
    play.loadImgui();

    logoTxt = Texture(static_cast<std::string>("../Content/Engine/logo.png"));
    logoTxt.loadImgui();

    fileTextures[0] = Texture(static_cast<std::string>("../Content/Engine/audio.png"));
    fileTextures[0].loadImgui();

    fileTextures[1] = Texture(static_cast<std::string>("../Content/Engine/image.png"));
    fileTextures[1].loadImgui();

    fileTextures[2] = Texture(static_cast<std::string>("../Content/Engine/video.png"));
    fileTextures[2].loadImgui();

    fileTextures[3] = Texture(static_cast<std::string>("../Content/Engine/folder.png"));
    fileTextures[3].loadImgui();

    fileTextures[4] = Texture(static_cast<std::string>("../Content/Engine/font.png"));
    fileTextures[4].loadImgui();

    fileTextures[5] = Texture(static_cast<std::string>("../Content/Engine/obj.png"));
    fileTextures[5].loadImgui();

    fileTextures[6] = Texture(static_cast<std::string>("../Content/Engine/unknown.png"));
    fileTextures[6].loadImgui();

    fileTextures[7] = Texture(static_cast<std::string>("../Content/Engine/code.png"));
    fileTextures[7].loadImgui();
#endif
    ImGui::CreateContext();
    ImPlot::CreateContext();
    //ImTTY::Terminal.CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
    io.ConfigViewportsNoTaskBarIcon = true;

    ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    ImGuiStyle& style = ImGui::GetStyle();
    EditorTheme theme;
    if (!global.rendererSettings.themeLoc.empty())
        theme = EditorTheme(colTheme);

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    if (!global.rendererSettings.themeLoc.empty())
    {
        theme.useTheme();
        style.WindowRounding = theme.getWindowRounding();
#ifndef __MINGW32__
        if (std_filesystem::exists(theme.getFont().first))
        {
            ImFontConfig config;
            io.Fonts->AddFontFromFileTTF(theme.getFont().first.c_str(), (float)theme.getFont().second, &config, io.Fonts->GetGlyphRangesCyrillic());
            io.Fonts->AddFontFromFileTTF(theme.getFont().first.c_str(), (float)theme.getFont().second, &config, io.Fonts->GetGlyphRangesThai());
            io.Fonts->AddFontFromFileTTF(theme.getFont().first.c_str(), (float)theme.getFont().second, &config, io.Fonts->GetGlyphRangesVietnamese());

            io.Fonts->Build();
        }
#endif
    }

    if (global.bUsesVulkan)
    {
        ImGui_ImplGlfw_InitForVulkan(global.window.getWindow(), true);
        // to be implemented
        //ImGui_ImplVulkan_Init();
    }
    else
    {
        ImGui_ImplGlfw_InitForOpenGL(global.window.getWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 450");
    }
    tm.stopRecording();
    frameTimeData[0] = tm.getDuration();

    logger.consoleLog("Starting the renderer took: ", UVK_LOG_TYPE_NOTE, tm.getDuration(), "ms!");
}

void UVK::Editor::runEditor(FVector4& colour, GLFrameBuffer& fb, Camera& camera, UVK::Level* lvl)
{
#ifndef PRODUCTION
    static bool opt_fullscreen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowBgAlpha(1.0f);

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
    }
    else
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;


    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    bool bIsOpen = true;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &bIsOpen, window_flags | ImGuiWindowFlags_NoCollapse);

    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    displayEditor(colour, fb, camera, lvl);

    ImGui::Render();

    if (global.bUsesVulkan)
    {
        // To be implemented
        //ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), );
    }
    else
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void UVK::Editor::displayEditor(FVector4& colour, GLFrameBuffer& fb, Camera& camera, UVK::Level* lvl)
{
    ImGuiStyle& style = ImGui::GetStyle();

    if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-shift") == Keys::KeyPressed || Input::getAction("editor-shift") == Keys::KeyRepeat) && (Input::getAction("editor-level-saveas") == Keys::KeyPressed || Input::getAction("editor-level-saveas") == Keys::KeyRepeat))
    {
        bShowSaveLevelWidget = true;
    }
    else if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-level-save") == Keys::KeyPressed || Input::getAction("editor-level-save") == Keys::KeyRepeat))
    {
        // TODO: Change this for file indexing :D
        UVK::Level::save(global.levelLocation.c_str());
    }
    else if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-shift") == Keys::KeyPressed || Input::getAction("editor-shift") == Keys::KeyRepeat) && (Input::getAction("editor-new-file") == Keys::KeyPressed || Input::getAction("editor-new-file") == Keys::KeyRepeat))
    {
        bShowCreateFile1 = true;
    }
    else if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-level-new") == Keys::KeyPressed || Input::getAction("editor-level-new") == Keys::KeyRepeat))
    {
        bShowSaveWarning = true;
    }
    else if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-level-open") == Keys::KeyPressed || Input::getAction("editor-level-open") == Keys::KeyRepeat))
    {
        bShowOpenLevelWidget = true;
    }
    else if (((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && Input::getAction("editor-undo") == Keys::KeyPressed) && !bEditorUsingTextbox)
    {
        global.instance->stateTracker.undo();
    }
    else if (((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && Input::getAction("editor-redo") == Keys::KeyPressed) && !bEditorUsingTextbox)
    {
        global.instance->stateTracker.redo();
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save Level", keys.editor_level_save.c_str()))
            {
                // TODO: Change this for file indexing :D
                bShowDirectSaveWarning = true;
            }

            if (ImGui::MenuItem("Save Level As", keys.editor_level_saveas.c_str()))
            {
                bShowSaveLevelWidget = true;
            }

            if (ImGui::MenuItem("New Level", keys.editor_level_new.c_str()))
            {
                bShowSaveWarning = true;
            }

            if (ImGui::MenuItem("Open Level", keys.editor_level_open.c_str()))
            {
                bShowOpenLevelWidget = true;
            }

            if (ImGui::MenuItem("New File", keys.editor_new_file.c_str()))
            {
                bShowCreateFile1 = true;
            }

            if (ImGui::MenuItem("Remove File"))
            {
                bShowRemoveFile = true;
            }

            if (ImGui::MenuItem("Regenerate files"))
            {
                bShowGenerateWarning = true;
            }

            if (ImGui::MenuItem("Ship Project"))
            {
                bShowShip = true;
            }

            if (ImGui::MenuItem("Exit"))
            {
                //glfwSetWindowShouldClose(global.window.getWindow(), GL_TRUE);
                bShowExitWarning = true;
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", keys.editor_undo.c_str()))
            {
                global.instance->stateTracker.undo();
            }

            if (ImGui::MenuItem("Redo", keys.editor_redo.c_str()))
            {
                global.instance->stateTracker.redo();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::MenuItem("Game Settings"))
            {
                bShowGameSettings = true;
            }

            if (ImGui::MenuItem("Window Settings"))
            {
                bShowWindowSettings = true;
            }

            if (ImGui::MenuItem("Renderer Settings"))
            {
                bShowRendererSettings = true;
            }

            if (ImGui::MenuItem("Editor Keybind Settings"))
            {
                bShowKeybindSettings = true;
            }

            if (ImGui::MenuItem("Game Keybind Settings"))
            {
                bShowGameKeybinds = true;
            }

            if (ImGui::MenuItem("Theme Editor"))
            {
                bShowThemeSettings = true;
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::Checkbox("Filesystem", &bShowFilesystem);
            ImGui::Checkbox("Statistics", &bShowStatistics);
            ImGui::Checkbox("Viewport", &bShowViewport);
            ImGui::Checkbox("Details Panel", &bShowDetailsPanel);
            ImGui::Checkbox("Terminal Emulator", &bShowTerminalEmulator);
            ImGui::Checkbox("Scene Hierarchy", &bShowSceneHierarchy);
            ImGui::Checkbox("World Settings", &bShowWorldSettings);
            ImGui::Checkbox("Toolbar", &bShowToolbar);
            ImGui::Checkbox("Tools", &bShowTools);
            ImGui::Checkbox("Memory Editor", &bShowMemoryEditor);
            ImGui::Checkbox("Developer Console", &bShowDeveloperConsole);

            if (!moduleManager.getIndependentModules().empty())
            {
                ImGui::Separator();

                for (auto& a : moduleManager.getIndependentModules())
                {
                    ImGui::Checkbox(a.name, &a.bEnabled);
                }
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("More"))
        {
            if (ImGui::MenuItem("About us"))
            {
                bShowAboutUs = true;
            }

            if (ImGui::MenuItem("Help"))
            {
                bShowHelp = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();

    if (bShowDirectSaveWarning)
        Warnings::displaySaveWarning(bShowDirectSaveWarning);

    if (bShowExitWarning)
        Warnings::displayExitWarning(bShowExitWarning);

    if (bShowGenerateWarning)
        Warnings::displayGenerateWarning(bShowGenerateWarning);

    if (bShowSaveWarning)
        NewLevel::display(bShowSaveWarning);

    if (bShowSaveLevelWidget)
        bEditorUsingTextbox = SaveLevel::display(bShowSaveLevelWidget, location, colour) ? true : bEditorUsingTextbox;

    if (bShowOpenLevelWidget)
        bEditorUsingTextbox = OpenLevelWidget::display(openLevel, bShowOpenLevelWidget, frameTimeData[1], colour) ? true : bEditorUsingTextbox;

    if (bShowCreateFile1)
        bEditorUsingTextbox = CreateFile::display(fileOutLocation, bShowCreateFile1) ? true : bEditorUsingTextbox;

    if (bShowDetailsPanel)
        bEditorUsingTextbox = DetailsPanel::display(selectedEntity, lvl, bShowDetailsPanel, moduleManager, bDestroyEntity) ? true : bEditorUsingTextbox;

    if (bShowSceneHierarchy)
        SceneHierarchy::display(selectedEntity, entAppend, entNum, bShowSceneHierarchy);

    if (bShowViewport)
    {
        style.WindowPadding = ImVec2(0.0f, 0.0f);
        EditorViewport::display(fb, viewportWidth, viewportHeight, bShowViewport, camera, selectedEntity, UVK::Level::getPawn(lvl)->camera.projection().data(), bEditorViewportFocused);
        style.WindowPadding = ImVec2(8.0f, 8.0f);
    }

#ifndef __MINGW32__
    if (bShowFilesystem)
        bEditorUsingTextbox = Filesystem::display(pt, fileTextures, filesystemWidgetData, bShowFilesystem) ? true : bEditorUsingTextbox;
#endif

    if (bShowToolbar)
    {
        style.WindowPadding = ImVec2(0.0f, 0.0f);
        bEditorUsingTextbox = TopToolbar::display(play, projectName, moduleManager,bShowToolbar) ? true : bEditorUsingTextbox;
        style.WindowPadding = ImVec2(8.0f, 8.0f);
    }

    if (bShowTools)
        bEditorUsingTextbox = Tools::display(moduleManager, bShowTools) ? true : bEditorUsingTextbox;

    if (bShowTerminalEmulator)
        bEditorUsingTextbox = TerminalEmulator::display(terminalCommand, bFinalisedCommand, bShowTerminalEmulator) ? true : bEditorUsingTextbox;

    if (bShowMemoryEditor)
        ImGuiMemoryEditor::display(bShowMemoryEditor);

    if (bShowStatistics)
        Statistics::display(frameTimeData, bShowStatistics);

    if (bShowWorldSettings)
        bEditorUsingTextbox = WorldSettings::display(colour, global.ambientLight, global.levelName, bShowWorldSettings) ? true : bEditorUsingTextbox;

    if (bShowAboutUs)
        About::display(engineVersion, projectName, projectVersion, logoTxt, bShowAboutUs);

    if (bShowHelp)
        Help::display(bShowHelp);

    if (bShowRemoveFile)
        bEditorUsingTextbox = RemoveFile::display(bShowRemoveFile) ? true : bEditorUsingTextbox;

    if (bShowShip)
        bEditorUsingTextbox = Shipping::display(bShowShip) ? true : bEditorUsingTextbox;

    if (bShowWindowSettings)
        bEditorUsingTextbox = Settings::displayWindow(bShowWindowSettings) ? true : bEditorUsingTextbox;

    if (bShowRendererSettings)
        bEditorUsingTextbox = Settings::displayRenderer(bShowRendererSettings, filesystemWidgetData) ? true : bEditorUsingTextbox;

    if (bShowKeybindSettings)
        bEditorUsingTextbox = Settings::displayKeybindEditor(bShowKeybindSettings) ? true : bEditorUsingTextbox;

    if (bShowGameKeybinds)
        bEditorUsingTextbox = Settings::displayKeybindGame(bShowGameKeybinds) ? true : bEditorUsingTextbox;

    if (bShowThemeSettings)
        bEditorUsingTextbox = Settings::displayThemeEditor(bShowThemeSettings) ? true : bEditorUsingTextbox;

    if (bShowGameSettings)
        bEditorUsingTextbox = Settings::displayProjectSettings(projectName, projectVersion, engineVersion, startupLevel, bShowGameSettings) ? true : bEditorUsingTextbox;

    if (bShowDeveloperConsole)
        loggerwidget.displayFull(bShowDeveloperConsole);

    bool bReturn = false;
    moduleManager.renderIndependentModule(bReturn);
    bEditorUsingTextbox = bReturn ? true : bEditorUsingTextbox;
#endif
}

void UVK::Editor::beginFrame()
{
    if (global.bUsesVulkan)
    {
        ImGui_ImplVulkan_NewFrame();
    }
    else
    {
        ImGui_ImplOpenGL3_NewFrame();
    }
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
}

void UVK::Editor::destroyContext()
{
    play.destroy();
    logoTxt.destroy();
    for (auto& a : fileTextures)
    {
        a.destroy();
    }

    if (global.bUsesVulkan)
    {
        ImGui_ImplVulkan_Shutdown();
    }
    else
    {
        ImGui_ImplOpenGL3_Shutdown();
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#ifndef PRODUCTION
    ImPlot::DestroyContext();
#endif
    //ImTTY::Terminal.DestroyContext();
    global.window.destroyWindow();
}
#else
UVK::Editor::Editor()
{
    global.instance->editor = this;
}
#endif