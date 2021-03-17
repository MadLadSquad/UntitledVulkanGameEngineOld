// Window.hpp
// Last update 3/17/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include "../../Core/Events/Input/InputSystem.hpp"
#include "../Textures/Texture.hpp"
#include <glfw3.h>
#include <yaml.h>
#include "UVKLog.h"


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

        [[nodiscard]] GLFWwindow* getWindow() const
        {
            return windowMain;
        }

        [[maybe_unused]] [[nodiscard]] FVector2 getLastMousePosition() const
        {
            return FVector2(lastPosX, lastPosY);
        }

        [[maybe_unused]] [[nodiscard]] FVector2 getCurrentMousePosition() const
        {
            return FVector2(posX, posY);
        }

        [[nodiscard]] FVector2 getMousePositionChange() const
        {
            return FVector2(offsetX, offsetY);
        }

        [[maybe_unused]] [[nodiscard]] FVector2 getScrollVal() const
        {
            return FVector2(scrollX, scrollY);
        }

        [[maybe_unused]] void setCursorVisibility(bool bIsVisible)
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

        int getBufferWidth()
        {
            return bufferWidth;
        }


        int getBufferHeight()
        {
            return bufferHeight;
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

        int bufferWidth, bufferHeight;
    };
}

inline UVK::Window currentWindow;