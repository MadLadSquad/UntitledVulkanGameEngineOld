#pragma once
#include "../../Core/API/Defines.h"

#ifdef Legacy
#include "../../ThirdParty/GLEW/include/GL/glew.h"
#include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"

namespace UVK
{
	class UVK_API GLWindow
	{
	public:
		GLWindow();
		
		GLFWwindow* CreateWindow(int Width, int Height);

		int CloseWindow(GLFWwindow* Window);

		GLFWwindow* Window;

		bool* GetKeys() 
		{ 
			return Keys;
		}


		GLfloat GetMouseXChange();
		GLfloat GetMouseYChange();

	private:
		void InitKeys();
		
		bool* Keys = new bool[1024];

		GLfloat LastMouseX = 0.0f;
		GLfloat LastMouseY = 0.0f;
		GLfloat MouseXChange = 0.0f;
		GLfloat MouseYChange = 0.0f;
		bool MouseInitialMovement = true;

		void DoCallBacks();

		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void KeyHandle(GLFWwindow* window, int key, int code, int action, int mode);
		static void MouseHandle(GLFWwindow* window, double xpos, double ypos);
	};
}
#endif