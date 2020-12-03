#include "GLRenderer.hpp"
#ifndef Production
#include "../../ThirdParty/imgui/imgui.h"
#include "../../ThirdParty/imgui/Platforms/imgui_impl_opengl3.h"
#include "../../ThirdParty/imgui/Platforms/imgui_impl_glfw.h"
#include "../../Editor/DetailsPanel.hpp"
#include "../../Editor/Statistics.hpp"
#endif

#ifdef Legacy
namespace UVK 
{
	//void GLRenderer::CreateShaders()
	//{
	//	GLShader* shader1 = new GLShader();
	//	shader1->CreateFromFiles(vShader, fShader);
	//	shaderList.push_back(*shader1);
	//}
	//void GLRenderer::CreateTriangle()
	//{
	//	uint32_t indices[] = {
	//		0, 3, 1,
	//		1, 3, 2,
	//		2, 3, 0,
	//		0, 1, 2
	//	};
	//
	//	GLfloat vertices[] = {
	//		-1.0f, -1.0f, 0.0f,
	//		0.0f, -1.0f, 1.0f,
	//		1.0f, -1.0f, 0.0f,
	//		0.0f, 1.0f, 0.0f
	//	};
	//
	//	GLMesh* obj1 = new GLMesh();
	//	obj1->CreateMesh(vertices, indices, 12, 12);
	//	meshList.push_back(obj1);
	//
	//	GLMesh* obj2 = new GLMesh();
	//	obj2->CreateMesh(vertices, indices, 12, 12);
	//	meshList.push_back(obj2);
	//
	//}

	/*
	int GLRenderer::InitWindow()
	{		
		//auto Window = WindowInit();
		
		// This is debug only
		CreateTriangle();
		CreateShaders();
		glm::mat4 Projection = glm::perspective(45.0f, (GLfloat)Width/(GLfloat)Height, 0.1f, 100.0f);

		// Loop until window closed
		while (!glfwWindowShouldClose(Window))
		{
			StartRenderer();

			//glUseProgram(shader);
			
			shaderList[0].UseShader();
			UniformModel = shaderList[0].GetModelLocation();
			UniformProjection = shaderList[0].GetProjectionLocation();

			glm::mat4 model(1.0f);

			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
			glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(UniformProjection, 1, GL_FALSE, glm::value_ptr(Projection));
			meshList[0]->RenderMesh();

			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
			glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
			meshList[1]->RenderMesh();

			glUseProgram(0);

			Editor(Window);

		}

		return DestroyWindow(Window);
	}
	*/
	void GLRenderer::ImGUIInit(GLFWwindow* Window)
	{
#ifndef Production
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigViewportsNoTaskBarIcon = true;

		io.FontDefault = io.Fonts->AddFontFromFileTTF("Content/Textures/Font/Roboto-Regular.ttf", 16.0f);

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkTheme();
		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(Window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
#endif
		glEnable(GL_DEPTH_TEST);
		

		// Setup Viewport size
		//glViewport(0, 0, Width, Height);	
	}

	int GLRenderer::DestroyWindow(GLFWwindow* Window)
	{
#ifndef Production
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
#endif
		window->CloseWindow(Window);

		return 0;
	}

	void GLRenderer::Editor(GLFWwindow* Window)
	{		
#ifndef Production
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
				if (ImGui::Button("New level"))
				{

				}

				if (ImGui::Button("Open level"))
				{

				}

				if (ImGui::Button("Exit"))
				{
					glfwSetWindowShouldClose(Window, GL_TRUE);
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

		{
			ImGui::Begin("Details");
			ImGui::End();
		}

		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
			ImGui::Begin("Scene Hierarchy");


			ImGui::End();
		}

		{
			ImGui::Begin("Transform");

			ImGui::Text("Translation");
			//if (ImGui::InputText(""))
			{

			}


			ImGui::End();
		}

		{
			UVKEditor::ShowStatisticsPanel();
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
#endif

		glfwSwapBuffers(Window);

	}

	void GLRenderer::StartRenderer(GLFWwindow* Window)
	{
		GLfloat now = glfwGetTime();
		DeltaTime = now - LastTime;
		LastTime = now;

		
		
		glClearColor(1.0, 1.0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifndef Production
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
#endif
		glfwPollEvents();
	}
	
	GLFWwindow* GLRenderer::WindowInit()
	{
		return window->CreateWindow(Width, Height);
	}
	
	void GLRenderer::SetDarkTheme()
	{
#ifndef Production
		auto& colours = ImGui::GetStyle().Colors;
		
		colours[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };
		
		colours[ImGuiCol_Header] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
		colours[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
		colours[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		
		colours[ImGuiCol_Button] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
		colours[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
		colours[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		
		colours[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
		colours[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
		colours[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

		colours[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		colours[ImGuiCol_TabHovered] = ImVec4{ 0.4f, 0.4f, 0.4f, 1.0f };
		colours[ImGuiCol_TabActive] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
		colours[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		colours[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
		
		colours[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		colours[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
		colours[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.95f, 0.15f, 0.95f, 1.0f };
#endif
	}
}

#endif