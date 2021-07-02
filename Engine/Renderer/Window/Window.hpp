// Window.hpp
// Last update 30/6/2021 by Madman10K
#pragma once
#include <GL/glew.h>
#include "../Textures/Texture.hpp"
#include <glfw3.h>
#include <yaml.h>
#include "UVKLog.h"

namespace UVK
{
    struct InputAction
    {
        InputAction() = default;
        bool operator==(uint16_t st) const
        {
            return state == st;
        }

        std::string name{};
        uint16_t keyCode{};
        uint16_t state{};
    };

    /**
     * @brief A standard cross-renderer window abstraction
     */
    class Window
    {
    public:
        Window();

        [[nodiscard]] GLFWwindow* getWindow() const;

        [[nodiscard]] int getBufferWidth() const;
        [[nodiscard]] int getBufferHeight() const;

        [[nodiscard]] FVector2 getLastMousePosition() const;
        [[nodiscard]] FVector2 getCurrentMousePosition() const;
        FVector2 getMousePositionChange();
        FVector2 getScroll();

        void setCursorVisibility(bool bIsVisible);
        void setTitle(UVK::String newTitle) const;
        void dumpConfig();
    private:
        friend class GLPipeline;
        friend class Renderer;
        friend class VulkanRenderer;
        friend class Input;
        friend class Editor;

        void createWindow();
        void destroyWindow();

        std::array<uint16_t, 350> keysArr{};
        const std::array<uint16_t, 350>& getKeys();

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

//inline UVK::Window currentWindow{};

namespace UVK
{
    /**
     * @brief A standard cross-renderer input abstraction
     */
    class Input
    {
    public:
        // Given a valid keyboard key from the Keys namespace it will return weather the key was pressed
        static uint16_t getKey(uint16_t key);

        static const InputAction& getAction(const std::string& name);

        static FVector2 getMousePositionChange();
        static FVector2 getCurrentMousePosition();
        static FVector2 getLastMousePosition();

        static FVector2 getScroll();
    private:
    };
}
