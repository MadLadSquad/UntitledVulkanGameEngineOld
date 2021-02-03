// GLRenderer.hpp
// Last update 1/10/2021 by Madman10K
#include "GLRenderer.hpp"
#include "../../Core/Events/Events.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"
#include "../EditorUI/DetailsPanel.hpp"
#include "../EditorUI/SaveLevel.hpp"


const GLint WIDTH = 800, HEIGHT = 600;
GLuint VBO, VAO, shader;
static const char* vShader = R"(
#version 460

layout (location = 0) in vec3 pos;

void main()
{
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
})";

static const char* fShader = R"(
#version 460

out vec4 colour;

void main()
{
    colour = vec4(1.0, 0.0, 0.0, 1.0);
})";

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
    std::string location;
    std::string name;
    bSetBuff = true;
    bShowSaveLevelWidget = false;

    logger.consoleLog("Creating geometry", NOTE);
    createTriangle();
    compileShaders();
    logger.consoleLog("Compiled Shaders", SUCCESS);

    Texture texture("icon.png");
    texture.load();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
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
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");


    events.callBegin();
    GLfloat DeltaTime = 0;
    GLfloat LastTime = 0;

    while (!glfwWindowShouldClose(window.getWindow()))
    {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glfwPollEvents();

        GLfloat now = glfwGetTime();
        DeltaTime = now - LastTime;
        LastTime = now;

        events.callTick(DeltaTime);

        glClearColor(1.0f, 0.8f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

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

        //if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &bIsOpen, window_flags);

        if (!opt_padding)
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

                if (ImGui::Button("Exit"))
                {
                    glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
                    return;
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
            SaveLevel::Display(bShowSaveLevelWidget, location, name);
        }

        if (bShowOpenLevelWidget)
        {
            ImGui::Begin("Open Level");
            char buffer[256];

            ImGui::InputText("File location", buffer, 256);
            if (ImGui::Button("Cancel"))
            {
                bShowOpenLevelWidget = false;
            }

            ImGui::SameLine();
            if (ImGui::Button("Submit"))
            {
                level->open(buffer);
                bShowOpenLevelWidget = false;
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
            DetailsPanel::Display(selectedEntity);
        }

        {
            ImGui::Begin("File System");

            ImGui::Text("Coming soon!");



            ImGui::Image((void*)(intptr_t)texture.getImage(), ImVec2(texture.getWidth(), texture.getHeight()));


            ImGui::End();
        }

        {
            ImGui::Begin("Toolbar");
            ImGui::Text("Coming soon!");
            ImGui::End();
        }

        {
            ImGui::Begin("Tools");

            ImGui::Text("Coming soon!");

            ImGui::End();
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
        glfwSwapBuffers(window.getWindow());
    }
    events.callEnd();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window.destroyWindow();
}

void UVK::GLRenderer::createTriangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void UVK::GLRenderer::addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = static_cast<std::string>(shaderCode).length();

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar ErrorLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, 1024, NULL, ErrorLog);
        logger.consoleLogComplex<GLchar*>("Error compiling the a shader:", ERROR, {ErrorLog});
        return;
    }

    glAttachShader(theProgram, theShader);
}

void UVK::GLRenderer::compileShaders()
{
    shader = glCreateProgram();

    if (!shader)
    {
        logger.consoleLog("Failed to create shader", ERROR);
        return;
    }

    addShader(shader, vShader, GL_VERTEX_SHADER);
    addShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(ErrorLog), NULL, ErrorLog);
        logger.consoleLogComplex<GLchar*>("Error linking program:", ERROR, {ErrorLog});
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(ErrorLog), NULL, ErrorLog);
        logger.consoleLogComplex<GLchar*>("Error validating program:", ERROR, {ErrorLog});
        return;
    }
}
