
#include "GLWindow.h"
#ifdef Legacy
#define STB_IMAGE_IMPLEMENTATION
#include "../../ThirdParty/stb_/stb_image.h"

UVK::GLWindow::GLWindow()
{
	for (size_t i = 0; i < 1024; i++)
	{
		Keys[i] = 0;
	}

	LastMouseX = 0.0f;
	LastMouseY = 0.0f;
	MouseInitialMovement = true;
	MouseXChange = 0.0f;
	MouseYChange = 0.0f;
}

GLFWwindow* UVK::GLWindow::CreateWindow(int Width, int Height)
{
	//InitKeys();
	
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return nullptr;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	Window = glfwCreateWindow(Width, Height, "Untitled Vulkan Game Engine 2", NULL, NULL);

	if (!Window)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return nullptr;
	}
	GLFWimage images[1];
	images[0].pixels = stbi_load("cd_drive-3.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
	glfwSetWindowIcon(Window, 1, images);
	stbi_image_free(images[0].pixels);

	glEnable(GL_MULTISAMPLE);

	glfwGetFramebufferSize(Window, &Width, &Height);

	glfwMakeContextCurrent(Window);

	DoCallBacks();
#ifndef Production
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
	glfwSwapInterval(0);
	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(Window);
		glfwTerminate();
		return nullptr;
	}

	glfwSetWindowUserPointer(Window, this);

	return Window;
}

int UVK::GLWindow::CloseWindow(GLFWwindow* Window)
{
	glfwDestroyWindow(Window);
	glfwTerminate();

	return 0;
}

GLfloat UVK::GLWindow::GetMouseXChange()
{
	GLfloat Change = MouseXChange;
	MouseXChange = 0.0f;

	return Change;
}

GLfloat UVK::GLWindow::GetMouseYChange()
{
	GLfloat Change = MouseYChange;
	MouseYChange = 0.0f;

	return Change;
}

void UVK::GLWindow::InitKeys()
{
	for (size_t i = 0; i < 1024; i++)
	{
		Keys[i] = 0;
	}

	LastMouseX = 0.0f;
	LastMouseY = 0.0f; 
	MouseInitialMovement = true;
	MouseXChange = 0.0f;
	MouseYChange = 0.0f;
}

void UVK::GLWindow::DoCallBacks()
{
	glfwSetFramebufferSizeCallback(Window, FramebufferSizeCallback);
	glfwSetKeyCallback(Window, KeyHandle);
	glfwSetCursorPosCallback(Window, MouseHandle);
}

void UVK::GLWindow::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void UVK::GLWindow::KeyHandle(GLFWwindow* window, int key, int code, int action, int mode)
{
	GLWindow* Window = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			Window->Keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Window->Keys[key] = false;
		}
	}
}

void UVK::GLWindow::MouseHandle(GLFWwindow* window, double xpos, double ypos)
{
	GLWindow* Window = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (Window->MouseInitialMovement)
	{
		Window->LastMouseX = xpos;
		Window->LastMouseY = ypos;
		Window->MouseInitialMovement = false;
	}

	Window->MouseXChange = xpos - Window->LastMouseX;
	Window->MouseYChange = Window->LastMouseY - ypos;

	Window->LastMouseX = xpos;
	Window->LastMouseY = ypos;
}


#endif