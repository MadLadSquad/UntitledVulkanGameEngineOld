// Window.hpp
// Last update 18/7/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    struct InputAction
    {
        InputAction() = default;
        bool operator==(uint8_t st) const
        {
            return state == st;
        }

        std::string name{};
        uint16_t keyCode{};
        uint8_t state{};
    };

    struct WindowData
    {
        WindowData() = default;

        bool fullscreen = false;
        std::string image = "../Content/Engine/icon.png";
        std::string name = "Untitled Vulkan Game Engine Editor";
        FVector2 size = FVector2(800, 600);
    };

    /**
     * @brief A standard cross-renderer window abstraction
     */
    class WindowInternal
    {
    public:
        WindowInternal();
    private:
        [[nodiscard]] GLFWwindow* getWindow() const;

        [[nodiscard]] int getBufferWidth() const;
        [[nodiscard]] int getBufferHeight() const;

        void setCursorVisibility(bool bIsVisible);
        void setTitle(UVK::String newTitle);
        void dumpConfig();

        WindowData& data();

        static void saveEditorKeybinds();
        static void saveGameKeybinds();
        void saveWindowSettings();

        friend class GLPipeline;
        friend class Renderer;
        friend class GLRenderer;
        friend class VulkanRenderer;
        friend class VKSwapchain;
        friend class Input;
        friend class Editor;
        friend class APawn;
        friend class Window;
        friend class SettingsManager;
        friend class UIInternal;

        [[nodiscard]] FVector2 getLastMousePosition() const;
        [[nodiscard]] FVector2 getCurrentMousePosition() const;
        FVector2 getMousePositionChange();
        FVector2 getScroll();

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

        WindowData resources;

        GLFWwindow* windowMain = nullptr;

        bool bFirstMove = true;

        double posX = 0;
        double posY = 0;
        double lastPosX = 0;
        double lastPosY = 0;
        double offsetX = 0;
        double offsetY = 0;
    };
}

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