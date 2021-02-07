// Window.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include "../../Core/Events/Input/InputSystem.hpp"
#include <glfw3.h>
#include <yaml.h>
#include "UVKLog.h"
#include "../Textures/Texture.hpp"

namespace UVK
{
    class Window
    {
    public:
        Window() = default;

        void createWindow();

        void dumpConfig();

        void destroyWindow();

        void setTitle(const std::string& newTitle) const
        {
            glfwSetWindowTitle(windowMain, newTitle.c_str());
        }

        GLFWwindow* getWindow() const
        {
            return windowMain;
        }

        FVector2 getLastMousePosition()
        {
            return FVector2(lastPosX, lastPosY);
        }

        FVector2 getCurrentMousePosition()
        {
            return FVector2(posX, posY);
        }

        FVector2 getMousePositionChange()
        {
            return FVector2(offsetX, offsetY);
        }

        FVector2 getScrollVal()
        {
            return FVector2(scrollX, scrollY);
        }

        void setCursorVisibility(bool bIsVisible)
        {
            if (bIsVisible)
            {
                glfwSetInputMode(windowMain, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(windowMain, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }

    private:

        void openConfig();
        void doCallBacks();

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
        static void mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods);
        static void mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset);

        std::string image = "icon.png";
        int width = 800;
        int height = 600;
        bool bIsFullScreen = false;

        std::string name = "Editor";

        GLFWwindow* windowMain = nullptr;

        bool bFirstMove = true;

        GLdouble posX = 0;
        GLdouble posY = 0;
        GLdouble lastPosX = 0;
        GLdouble lastPosY = 0;
        GLdouble offsetX = 0;
        GLdouble offsetY = 0;

        GLdouble scrollX = 0;
        GLdouble scrollY = 0;
    };
}

inline UVK::Window window;