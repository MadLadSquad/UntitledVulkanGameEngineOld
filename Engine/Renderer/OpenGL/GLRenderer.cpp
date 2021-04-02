// GLRenderer.cpp
// Last update 3/27/2021 by Madman10K
#include "Components/GLMesh.hpp"
#include "Components/GLCamera.hpp"
#include "GLRenderer.hpp"
#include "../../Core/Events/Events.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"
#include "../EditorUI/DetailsPanel.hpp"
#include "../EditorUI/SaveLevel.hpp"
//#include "../EditorUI/Filesystem.hpp"
#include "../EditorUI/Statistics.hpp"
#include "../EditorUI/WorldSettings.hpp"
#include "../imguiex/memory_editor/imgui_memory_editor.h"

void UVK::GLRenderer::renderEditor(Texture& play)
{

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
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
    ImGui::Begin("DockSpace Demo", &bIsOpen, window_flags);
    
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
                pool.clear();
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
                std::terminate();
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
        ImGui::EndMenuBar();
    }

    ImGui::End();

    if (bShowSaveLevelWidget)
    {
        SaveLevel::display(bShowSaveLevelWidget, location, name);
    }

    if (bShowOpenLevelWidget)
    {
        ImGui::Begin("Open Level");

        ImGui::InputText("File location", &openLevel);
        if (ImGui::Button("Cancel"))
        {
            bShowOpenLevelWidget = false;
        }

        ImGui::SameLine();
        if (ImGui::Button("Submit"))
        {
            UVK::Level::open(openLevel.c_str());
            bShowOpenLevelWidget = false;
        }


        ImGui::End();
    }

    if (bShowCreateFile1)
    {
        ImGui::Begin("Create a file");

        // This is so the linter can shut up
        int lnt = 0;

        if (ImGui::Selectable("Game mode")) selectedFile = 1;
        if (ImGui::Selectable("Game state")) selectedFile = 2;
        if (ImGui::Selectable("Player state")) selectedFile = 3;
        if (ImGui::Selectable("Player controller")) selectedFile = 4;
        if (ImGui::Selectable("Pawn")) selectedFile = 5;
        if (ImGui::Selectable("Game instance")) selectedFile = 6;
        if (ImGui::Selectable("Level")) selectedFile = 7;

        ImGui::InputTextWithHint("Location##genfile", "Location starts from your Source folder!", &fileOutLocation);

        if (ImGui::Button("Create"))
        {
            switch(selectedFile)
            {
                case 1:
#ifdef _WIN32
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --game-mode " + fileOutLocation + "cd ../../").c_str());
#else
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --game-mode " + fileOutLocation + "cd ../../").c_str());
#endif
                    break;
                case 2:
#ifdef _WIN32
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --game-state " + fileOutLocation + "cd ../../").c_str());
#else                    
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --game-state " + fileOutLocation + "cd ../../").c_str());
#endif
                    break;
                case 3:
#ifdef _WIN32
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --player-state " + fileOutLocation + "cd ../../").c_str());
#else                    
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --player-state " + fileOutLocation + "cd ../../").c_str());
#endif
                    break;
                case 4:
#ifdef _WIN32                    
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --player-controller " + fileOutLocation + "cd ../../").c_str());
#else                    
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --player-controller " + fileOutLocation + "cd ../../").c_str());
#endif                    
                    break;
                case 5:
#ifdef _WIN32      
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --pawn " + fileOutLocation + "cd ../../").c_str());
#else           
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --pawn " + fileOutLocation + "cd ../../").c_str());
#endif  
                    break;
                case 6:
#ifdef _WIN32 
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --game-instance " + fileOutLocation + "cd ../../").c_str());
#else
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --game-instance " + fileOutLocation + "cd ../../").c_str());
#endif  
                    break;
                case 7:
#ifdef _WIN32
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --level " + fileOutLocation + "cd ../../").c_str());
#else
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --level " + fileOutLocation + "cd ../../").c_str());
#endif   
                    break;
                default:
                    break;
            }

            if (!lnt)
            {
                logger.consoleLog("Error when generating files!", UVK_LOG_TYPE_ERROR, lnt);
            }

            selectedFile = 0;
            bShowCreateFile1 = false;
            fileOutLocation = "";
        }
        if (ImGui::Button("Cancel"))
        {
            selectedFile = 0;
            bShowCreateFile1 = false;
            fileOutLocation = "";
        }

        ImGui::End();
    }
    
    {
        ImGui::Begin("Scene Hierarchy");

        pool.each([&](entt::entity ent)
        {
            auto& a = registry.getComponent<CoreComponent>(ent);

            if (ImGui::Selectable(a.name.c_str()))
            {
                selectedEntity = ent;
            }
        });

        ImGui::End();
    }

    {
        DetailsPanel::display(selectedEntity);
    }
    
#ifndef __MINGW32__
    {
        //Filesystem::display(folder, audio, model, pt);
    }
#endif
        
    {
        int lnt = 0;

        ImGui::Begin("Toolbar");
        
        if (ImGui::ImageButton((void*)(intptr_t)play.getImage(), ImVec2((float)play.getWidth(), (float)play.getHeight())))
        {
#ifdef _WIN32
            lnt = system("Game.exe");
#else
            lnt = system("./Game");
#endif
        }

        if (lnt)
        {

        }

        ImGui::End();
    }
    
    {
        ImGui::Begin("Tools");
    
        ImGui::Text("Coming soon!");
    
        ImGui::End();
    }
    
    {
        ImGui::Begin("Memory Editor");
        int hello = 50;
    
        //ImGui::InputInt("Memory size", siz));
    
        static MemoryEditor mem_edit;
    
        mem_edit.DrawContents(&hello, sizeof(char*));
    
        ImGui::End();
    }
    
    {
        Statistics::display();
    }
    
    {
        WorldSettings::display(colour, FVector4(1.0f, 1.0f, 1.0f, 1.0f), levelName);
    }
    
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

void UVK::GLRenderer::initEditor() const
{
    if (bEditor)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImPlot::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigViewportsNoTaskBarIcon = true;


        ImGui::StyleColorsDark();
        ImGui::StyleColorsClassic();


        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        setDarkTheme();
        ImGui_ImplGlfw_InitForOpenGL(currentWindow.getWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_STENCIL_TEST);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void UVK::GLRenderer::loadResources()
{

}

void UVK::GLRenderer::setDarkTheme()
{
    auto& colours = ImGui::GetStyle().Colors;

    colours[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.1f, 0.85f };

    colours[ImGuiCol_Header] = ImVec4{ 0.2f, 0.2f, 0.2f, 0.85f };
    colours[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 0.85f };
    colours[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 0.85f };

    colours[ImGuiCol_Button] = ImVec4{ 0.2f, 0.2f, 0.2f, 0.85f };
    colours[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 0.85f };
    colours[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 0.85f };

    colours[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.2f, 0.2f, 0.85f };
    colours[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 0.85f };
    colours[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 0.85f };

    colours[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.15f, 0.15f, 0.85f };
    colours[ImGuiCol_TabHovered] = ImVec4{ 0.4f, 0.4f, 0.4f, 0.85f };
    colours[ImGuiCol_TabActive] = ImVec4{ 0.3f, 0.3f, 0.3f, 0.85f };
    colours[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.15f, 0.15f, 0.85f };
    colours[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.2f, 0.2f, 0.85f };

    colours[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.15f, 0.15f, 0.85f };
    colours[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 0.85f };
    colours[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.95f, 0.15f, 0.95f, 0.85f };

    colours[ImGuiCol_MenuBarBg] = ImVec4{ 0.01, 0.01, 0.01, 0.85f };
}

void UVK::GLRenderer::createWindow(UVK::Level* level) noexcept
{

    
    GLCamera cm = GLCamera(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 750.0f);
    
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f
    };

    currentWindow.createWindow();

    logger.consoleLog("Creating geometry", UVK_LOG_TYPE_NOTE);
    
    auto* sh = new GLShader();
#ifndef __MINGW32__
    std_filesystem::path res("../Content/Engine/");
    std_filesystem::path pt("../Content/");

    Texture folder(static_cast<std::string>(res.string() + "folder.png"));
    folder.loadImgui();
    //folder.useTexture();

    Texture audioImg(static_cast<std::string>(res.string() + "audio.png"));
    audioImg.loadImgui();

    Texture model(static_cast<std::string>(res.string() + "model.png"));
    model.loadImgui();

    Texture play(static_cast<std::string>(res.string() + "Play.png"));
    play.loadImgui();

    Texture brick(static_cast<std::string>(res.string() + "brick.jpg"));
    brick.load();

    sh->createFromFile(static_cast<std::string>(res.string() + "defaultvshader.gl").c_str(), static_cast<std::string>(res.string() + "defaultfshader.gl").c_str());
#else
    Texture folder(static_cast<std::string>("../Content/Engine/folder.png"));
    folder.loadImgui();

    Texture audio(static_cast<std::string>("../Content/Engine/audio.png"));
    audio.loadImgui();

    Texture model(static_cast<std::string>("../Content/Engine/model.png"));
    model.loadImgui();

    Texture play(static_cast<std::string>("../Content/Engine/Play.png"));
    play.loadImgui();

    Texture brick(static_cast<std::string>("../Content/Engine/brick.jpg"));
    brick.load();

    sh->createFromFile("../Content/Engine/defaultvshader.gl", "../Content/Engine/defaultfshader.gl");
#endif

    MeshComponentRaw ms;
    ms.createMesh(vertices, indices, 20, 12, "../Content/Engine/vert.spv", "../Content/Engine/frag.spv", SHADER_IMPORT_TYPE_FILE);

    // Will soon be removed because uniforms bad
    //GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (GLfloat)currentWindow.getBufferWidth() / (GLfloat)currentWindow.getBufferHeight(), 0.1f, 100.0f);
    logger.consoleLog("Compiled Shaders", UVK_LOG_TYPE_SUCCESS);


    initEditor();

    logger.consoleLog("Init editor", UVK_LOG_TYPE_SUCCESS);

    if (!bEditor)
    {
        events.callBegin();
    }
    
    GLfloat deltaTime;
    GLfloat lastTime = 0;
    
    colour = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
    while (!glfwWindowShouldClose(currentWindow.getWindow()))
    {        
        glfwPollEvents();

        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        cm.move(deltaTime);
        cm.moveMouse(deltaTime, UVK::Input::getMousePositionChange());

        glClearColor(colour.x, colour.y, colour.z, colour.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (bEditor)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            events.callTick(deltaTime);
        }
        
        Model mat = Model();

        mat.translate(FVector(0.0f, 2.0f, -2.5f));
        mat.rotate(90.0f, FVector(0.0f, 1.0f, 0.0f));
        mat.scale(FVector(1.0f, 1.0f, 1.0f));
        brick.useTexture();
        ms.render(projection, mat, cm);
        
        glUseProgram(0);

        if (bEditor)
        {
            level->tick(deltaTime);
            renderEditor(play);
        }

        glfwSwapBuffers(currentWindow.getWindow());
    }
    events.callEnd();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();
    currentWindow.destroyWindow();
}