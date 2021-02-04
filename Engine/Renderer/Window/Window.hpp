// Window.hpp
// Last update 1/10/2021 by Madman10K
#pragma once
#ifdef __APPLE__
#define NO_GLEW
#else
#undef NO_GLEW
#endif

#ifdef NO_GLEW
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <glfw3.h>
#include <yaml.h>
#include "UVKLog.h"
#include "../Textures/Texture.hpp"

namespace UVK
{
    class Window
    {
    public:
        Window()
        {
            createWindow();
        }

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