// Window.hpp
// Last update 3/26/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include "../Textures/Texture.hpp"
#include <glfw3.h>
#include <yaml.h>
#include "UVKLog.h"


namespace UVK
{
    class Window
    {
    public:
        Window()
        {
            for (auto& a : keysArr)
            {
                a = false;
            }

            for (auto& b : mouseArr)
            {
                b = false;
            }
        }

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

        [[nodiscard]] FVector2 getScrollVal() const
        {
            auto a = FVector2(scrollX, scrollY);

            //scrollX = 0;
            //scrollY = 0;

            return a;
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

        [[nodiscard]] int getBufferWidth() const
        {
            return bufferWidth;
        }
        
        FVector2 getMousePositionChage()
        {
            return FVector2(getXMousePositionChange(), getYMousePositionChange());
        }

        [[nodiscard]] int getBufferHeight() const
        {
            return bufferHeight;
        }
        std::array<bool, 142> keysArr{};
        std::array<bool, 20> mouseArr{};
    private:

        void openConfig();
        void doCallBacks();

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
        static void mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods);
        static void mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset);

        [[nodiscard]] double getXMousePositionChange()
        {
            GLfloat a = offsetX;
            offsetX = 0.0f;

            return a;
        }

        [[nodiscard]] double getYMousePositionChange()
        {
            GLfloat a = offsetY;
            offsetY = 0.0f;

            return a;
        }

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

        int bufferWidth = 0;
        int bufferHeight = 0;
    };
}

inline UVK::Window currentWindow;

namespace UVK
{
    class Input
    {
    public:
        Input() = default;

        static bool getKeyPressed(const int key)
        {
            if (currentWindow.keysArr[key])
            {
                return true;
            }

            return false;
        }

        static bool getMouseKeyPressed(const int key)
        {
            if (currentWindow.mouseArr[key])
            {
                return true;
            }

            return false;
        }

        static FVector2 getMousePositionChange()
        {
            return currentWindow.getMousePositionChage();
        }

        static FVector2 getCurrentMousePosition()
        {
            return currentWindow.getCurrentMousePosition();
        }

        static FVector2 getLastMousePosition()
        {
            return currentWindow.getLastMousePosition();
        }

        static FVector2 getMouseWheelMovement()
        {
            return currentWindow.getScrollVal();
        }
    private:
    };
}

inline UVK::Input input;