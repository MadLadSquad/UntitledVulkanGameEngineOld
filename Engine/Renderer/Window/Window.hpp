// Window.hpp
// Last update 1/10/2021 by Madman10K
#pragma once
#include <GL/glew.h>
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
        }
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

    private:

        void openConfig();
        void doCallBacks();

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

        std::string image = "icon.png";
        int width = 800;
        int height = 600;
        bool bIsFullScreen = false;

        std::string name = "Editor";

        GLFWwindow* windowMain = nullptr;
    };

    
}

inline UVK::Window window;