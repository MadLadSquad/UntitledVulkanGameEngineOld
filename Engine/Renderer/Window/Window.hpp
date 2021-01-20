// Window.hpp
// Last update 1/10/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include <yaml.h>
#include "UVKLog.h"

namespace UVK
{
    class Window
    {
    public:
        void createWindow();

        void dumpConfig();

        void destroyWindow();

        GLFWwindow* getWindow()
        {
            return windowMain;
        }


        void doCallBacks();

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    private:

        std::string image = "icon.png";
        int width = 800;
        int height = 600;
        bool bIsFullScreen = false;
        GLFWwindow* windowMain;
        std::string name = "Editor";
    };
}


inline UVK::Window window;