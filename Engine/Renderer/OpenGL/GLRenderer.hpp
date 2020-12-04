#pragma once
#include "../../Core/API/Defines.h"

#ifdef Legacy
#include "../../ThirdParty/GLEW/include/GL/glew.h"
#include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
#include "../../ThirdParty/GLM/glm/glm.hpp"
#include "../../ThirdParty/GLM/glm/gtc/type_ptr.hpp"
#include "GLCamera.hpp"
#include "GLWindow.h"
#include <vector>
#include <stdlib.h>
#include "GLMesh.hpp"
#include "GLShader.hpp"
#include <algorithm>
#include <string>

#define RENDERER_START(x) auto Window = x->WindowInit();\
x->ImGUIInit(Window);\
auto windowClose = glfwWindowShouldClose(Window);\
auto WindowInterface = x->GetWindow();

#define GAMELOOP_START(x) while (!x->GetShouldClose(Window)){x->StartRenderer(Window);

#define GAMELOOP_END(x) x->Editor(Window);}

#define RENDERER_END(x) return x->DestroyWindow(Window);

namespace UVK 
{
	class UVK_API GLRenderer
	{
	public:
		
		void ImGUIInit(GLFWwindow* Window);
		int DestroyWindow(GLFWwindow* Window);
		void Editor(GLFWwindow* Window);
		void StartRenderer(GLFWwindow* Window);
		GLFWwindow* WindowInit();

		bool GetShouldClose(GLFWwindow* Window) { return glfwWindowShouldClose(Window); }
	
		GLWindow* GetWindow()
		{
			return window;
		}

		GLfloat DeltaTime = 0.0f;
	private: 		
		bool bCreatedWindow = true;
		
		GLfloat LastTime = 0.0f;
		GLWindow* window = new GLWindow();
		int Width = 800;
		int Height = 600;
		
		void SetDarkTheme();

	};
}
#endif

