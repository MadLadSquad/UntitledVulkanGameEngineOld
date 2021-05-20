// Editor.cpp
// Last update 15/5/2021 by Madman10K
#include <GL/glew.h>
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"
#include "Widgets/SceneHierarchy.hpp"
#include "Editor.hpp"
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
#include "Widgets/NewLevel.hpp"
#include "Widgets/Help.hpp"
#include "../Window/Window.hpp"

void UVK::Editor::initEditor()
{
    Timer tm;
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
    EditorTheme theme(colTheme);
    //style.WindowPadding = ImVec2(0.0f, 0.0f);

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = theme.getWindowRounding();
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
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
    ImGui_ImplGlfw_InitForOpenGL(currentWindow.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 450");

    tm.stopRecording();
    frameTimeData[0] = tm.getDuration();

    logger.consoleLog("Starting the renderer took: ", UVK_LOG_TYPE_NOTE, tm.getDuration(), "ms!");
}

void UVK::Editor::runEditor(FVector4& colour, GLFrameBuffer& fb)
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
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

    displayEditor(colour, fb);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void UVK::Editor::displayEditor(FVector4& colour, GLFrameBuffer& fb)
{
    ImGuiStyle& style = ImGui::GetStyle();

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            int lnt;

            if (ImGui::Button("Save level"))
            {
                bShowSaveLevelWidget = true;
            }

            if (ImGui::Button("New level"))
            {
                bShowSaveWarning = true;
            }

            if (ImGui::Button("Open level"))
            {
                bShowOpenLevelWidget = true;
            }

            if (ImGui::Button("New File"))
            {
                bShowCreateFile1 = true;
            }

            if (ImGui::Button("Regenerate files"))
            {
#ifdef _WIN32
                lnt = system("cd ../UVKBuildTool/build/ && UVKBuildTool.exe --generate && cd ../../");
#else
                lnt = system("cd ../UVKBuildTool/build/ && ./UVKBuildTool --generate && cd ../../");
#endif

                if (!lnt)
                {
                    logger.consoleLog("Error when regenerating files!", UVK_LOG_TYPE_ERROR, lnt);
                }
            }

            if (ImGui::Button("Exit"))
            {
                glfwSetWindowShouldClose(currentWindow.getWindow(), GL_TRUE);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::Button("Undo"))
            {

            }

            if (ImGui::Button("Redo"))
            {

            }

            if (ImGui::Button("Undo history"))
            {

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
            if (ImGui::Button("About us"))
            {
                bShowAboutUs = true;
            }

            if (ImGui::Button("Help"))
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
        SaveLevel::display(bShowSaveLevelWidget, location, name);
    }

    if (bShowOpenLevelWidget)
    {
        OpenLevelWidget::display(openLevel, bShowOpenLevelWidget, frameTimeData[1]);
    }

    if (bShowCreateFile1)
    {
        CreateFile::display(selectedFile, fileOutLocation, bShowCreateFile1);
    }

    if (bShowSceneHierarchy)
    {
        SceneHierarchy::display(selectedEntity, entAppend, entNum, bShowSceneHierarchy);
    }

    if (bShowViewport)
    {
        style.WindowPadding = ImVec2(0.0f, 0.0f);

        EditorViewport::display(fb, viewportWidth, viewportHeight, bShowViewport);

        style.WindowPadding = ImVec2(8.0f, 8.0f);
    }

    if (bShowDetailsPanel)
    {
        DetailsPanel::display(selectedEntity, bShowDetailsPanel, bDestroyEntity);
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
        WorldSettings::display(colour, FVector4(1.0f, 1.0f, 1.0f, 1.0f), levelName, bShowWorldSettings);
    }

    if (bShowAboutUs)
    {
        About::display(engineVersion, projectName, projectVersion, logoTxt, bShowAboutUs);
    }

    if (bShowHelp)
    {
        Help::display(bShowHelp);
    }
}

void UVK::Editor::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
}

void UVK::Editor::destroyContext()
{
    play.destroy();
    logoTxt.destroy();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();
    //ImTTY::Terminal.DestroyContext();
    currentWindow.destroyWindow();
}