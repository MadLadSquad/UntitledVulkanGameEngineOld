// Editor.cpp
// Last update 6/7/2021 by Madman10K
#include <GL/glew.h>
#include <imgui_impl_vulkan.h>
#include "Editor.hpp"
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
#include <Engine/Core/Core/Global.hpp>
#include <Renderer/OpenGL/Components/GLShader.hpp>

void UVK::Editor::initEditor()
{
    Timer tm;
#ifndef PRODUCTION
    tm.startRecording();
#ifndef __MINGW32__
    pt = std_filesystem::absolute(std_filesystem::current_path());
#endif
    YAML::Node file;

    try
    {
        file = YAML::LoadFile("../uvproj.yaml");
    }
    catch (YAML::BadFile&)
    {
        logger.consoleLog("Could not find uvproj.yaml file", UVK_LOG_TYPE_ERROR);
    }

    if (file["engine-version"] && file["name"] && file["version"])
    {
        engineVersion = file["engine-version"].as<std::string>();
        projectVersion = file["version"].as<std::string>();
        projectName = file["name"].as<std::string>();
    }

    auto* sh = new GLShader();
#ifndef __MINGW32__

    play = Texture(static_cast<std::string>(pt.string() + "/../Content/Engine/Play.png"));
    play.loadImgui();

    logoTxt = Texture(static_cast<std::string>(pt.string() + "/../Content/Engine/logo.png"));
    logoTxt.loadImgui();

    insert = Texture(static_cast<std::string>(pt.string() + "/../Content/Engine/insert.png"));
    insert.loadImgui();

    sh->createFromFile(static_cast<std::string>(pt.string() + "/../Content/Engine/defaultvshader.gl").c_str(), static_cast<std::string>(pt.string() + "/../Content/Engine/defaultfshader.gl").c_str());
#else
    play = Texture(static_cast<std::string>("../Content/Engine/Play.png"));
    play.loadImgui();

    logoTxt = Texture(static_cast<std::string>("../Content/Engine/logo.png"));
    logoTxt.loadImgui();

    insert = Texture(static_cast<std::string>("../Content/Engine/insert.png"));
    insert.loadImgui();

    sh->createFromFile("../Content/Engine/defaultvshader.gl", "../Content/Engine/defaultfshader.gl");
#endif
    ImGui::CreateContext();
    ImPlot::CreateContext();
    //ImTTY::Terminal.CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigViewportsNoTaskBarIcon = true;

    ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    ImGuiStyle& style = ImGui::GetStyle();
    EditorTheme theme;
    if (!global.rendererSettings.themeLoc.empty())
    {
        theme = EditorTheme(colTheme);
    }

    //style.WindowPadding = ImVec2(0.0f, 0.0f);

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        if (!global.rendererSettings.themeLoc.empty())
        {
            style.WindowRounding = theme.getWindowRounding();
        }
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    if (!global.rendererSettings.themeLoc.empty())
    {
        theme.useTheme();
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
#endif
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

        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }


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
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

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
    else if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-shift") == Keys::KeyPressed || Input::getAction("editor-shift") == Keys::KeyRepeat) && (Input::getAction("editor-exit") == Keys::KeyPressed || Input::getAction("editor-exit") == Keys::KeyRepeat))
    {
        logger.consoleLog("Shutting down editor!", UVK_LOG_TYPE_NOTE);
        glfwSetWindowShouldClose(global.window.getWindow(), GL_TRUE);
    }


    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save Level", "CTRL+S"))
            {
                // TODO: Change this for file indexing :D
                UVK::Level::save(global.levelLocation.c_str());
            }

            if (ImGui::MenuItem("Save Level As", "CTRL+SHIFT+S"))
            {
                bShowSaveLevelWidget = true;
            }

            if (ImGui::MenuItem("New Level", "CTRL+N"))
            {
                bShowSaveWarning = true;
            }

            if (ImGui::MenuItem("Open Level", "CTRL+O"))
            {
                bShowOpenLevelWidget = true;
            }

            if (ImGui::MenuItem("New File", "CTRL+SHIFT+N"))
            {
                bShowCreateFile1 = true;
            }

            if (ImGui::MenuItem("Remove File"))
            {
                bShowRemoveFile = true;
            }

            if (ImGui::MenuItem("Regenerate files"))
            {
                int lnt;
#ifdef _WIN32
                lnt = system("cd ../UVKBuildTool/build/ && UVKBuildTool.exe --generate && cd ../../");
#else
                lnt = system("cd ../UVKBuildTool/build/ && ./UVKBuildTool --generate && cd ../../");
#endif

                if (lnt)
                {
                    logger.consoleLog("Error when regenerating files!", UVK_LOG_TYPE_ERROR, lnt);
                }
            }

            if (ImGui::MenuItem("Ship Project"))
            {
                bShowShip = true;
            }

            if (ImGui::MenuItem("Exit", "CTRL+SHIFT+W"))
            {
                glfwSetWindowShouldClose(global.window.getWindow(), GL_TRUE);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z"))
            {

            }

            if (ImGui::MenuItem("Redo", "CTRL+Y"))
            {

            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Settings"))
        {
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

    if (bShowSaveWarning)
    {
        NewLevel::display(bShowSaveWarning);
    }

    if (bShowSaveLevelWidget)
    {
        SaveLevel::display(bShowSaveLevelWidget, location, levelName, colour, insert, cpFileLoc);
    }

    if (bShowOpenLevelWidget)
    {
        OpenLevelWidget::display(openLevel, bShowOpenLevelWidget, frameTimeData[1], colour, levelName, insert, cpFileLoc);
    }

    if (bShowCreateFile1)
    {
        CreateFile::display(selectedFile, fileOutLocation, bShowCreateFile1, insert, cpFileLoc);
    }

    if (bShowSceneHierarchy)
    {
        SceneHierarchy::display(selectedEntity, entAppend, entNum, bShowSceneHierarchy);
    }

    if (bShowViewport)
    {
        style.WindowPadding = ImVec2(0.0f, 0.0f);
        EditorViewport::display(fb, viewportWidth, viewportHeight, bShowViewport, camera, selectedEntity, lvl->gameMode->pawn->camera.getProjection().data());
        style.WindowPadding = ImVec2(8.0f, 8.0f);
    }

    if (bShowDetailsPanel)
    {
        DetailsPanel::display(selectedEntity, lvl, bShowDetailsPanel, bDestroyEntity, insert, cpFileLoc);
    }

#ifndef __MINGW32__
    if (bShowFilesystem)
    {
        Filesystem::display(pt, cpFileLoc, bShowFilesystem);
    }
#endif

    if (bShowToolbar)
    {
        style.WindowPadding = ImVec2(0.0f, 0.0f);
        TopToolbar::display(play, bShowToolbar);
        style.WindowPadding = ImVec2(8.0f, 8.0f);
    }

    if (bShowTools)
    {
        ImGui::Begin("Tools", &bShowTools);
        ImGui::Text("Coming soon!");
        ImGui::End();
    }

    if (bShowTerminalEmulator)
    {
        TerminalEmulator::display(terminalCommand, bFinalisedCommand, bShowTerminalEmulator);
    }

    if (bShowMemoryEditor)
    {
        ImGuiMemoryEditor::display(bShowMemoryEditor);
    }

    if (bShowStatistics)
    {
        Statistics::display(frameTimeData, bShowStatistics);
    }

    if (bShowWorldSettings)
    {
        WorldSettings::display(colour, global.ambientLight, levelName, bShowWorldSettings, insert, cpFileLoc);
    }

    if (bShowAboutUs)
    {
        About::display(engineVersion, projectName, projectVersion, logoTxt, bShowAboutUs);
    }

    if (bShowHelp)
    {
        Help::display(bShowHelp);
    }

    if (bShowRemoveFile)
    {
        RemoveFile::display(bShowRemoveFile, insert, cpFileLoc);
    }

    if (bShowShip)
    {
        Shipping::display(bShowShip);
    }

    if (bShowWindowSettings)
    {
        Settings::displayWindow(bShowWindowSettings);
    }

    if (bShowRendererSettings)
    {
        Settings::displayRenderer(bShowRendererSettings);
    }

    if (bShowKeybindSettings)
    {
        Settings::displayKeybindEditor(bShowKeybindSettings);
    }

    if (bShowGameKeybinds)
    {
        Settings::displayKeybindGame(bShowGameKeybinds);
    }

    if (bShowThemeSettings)
    {
        Settings::displayThemeEditor(bShowThemeSettings);
    }
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