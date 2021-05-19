// Window.hpp
// Last update 18/5/2021 by Madman10K
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
        Window();


        void createWindow();
        void dumpConfig();
        void destroyWindow();

        void setTitle(const std::string& newTitle) const;
        [[nodiscard]] GLFWwindow* getWindow() const;
        [[nodiscard]] FVector2 getLastMousePosition() const;
        [[nodiscard]] FVector2 getCurrentMousePosition() const;


        void setCursorVisibility(bool bIsVisible);


        [[nodiscard]] int getBufferWidth() const
        {
            return bufferWidth;
        }
        
        FVector2 getMousePositionChange()
        {
            return FVector2(getXMousePositionChange(), getYMousePositionChange());
        }

        [[nodiscard]] int getBufferHeight() const
        {
            return bufferHeight;
        }

        const std::array<bool, 349>& getKeys();
        const std::array<bool, 20>& getMouseKeys();
        FVector2 getScroll();
    private:
        std::array<bool, 349> keysArr{};
        std::array<bool, 20> mouseArr{};

        FVector2 scroll{};

        void openConfig();
        void doCallBacks();

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
        static void mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods);
        static void mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset);

        [[nodiscard]] double getXMousePositionChange();
        [[nodiscard]] double getYMousePositionChange();

        std::string image = "../Content/Engine/icon.png";
        int width = 800;
        int height = 600;
        bool bIsFullScreen = false;
        std::string name = "Untitled Vulkan Game Engine Editor";

        GLFWwindow* windowMain = nullptr;

        bool bFirstMove = true;

        GLdouble posX = 0;
        GLdouble posY = 0;
        GLdouble lastPosX = 0;
        GLdouble lastPosY = 0;
        GLdouble offsetX = 0;
        GLdouble offsetY = 0;

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
        static bool getKeyPressed(int key);
        static bool getMouseKeyPressed(int key);

        static FVector2 getMousePositionChange();
        static FVector2 getCurrentMousePosition();
        static FVector2 getLastMousePosition();

        static FVector2 getScroll();
    private:
    };
}