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
    };
}


inline UVK::Window window;