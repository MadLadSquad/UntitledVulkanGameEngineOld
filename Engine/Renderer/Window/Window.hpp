// Window.hpp
// Last update 2/9/2021 by Madman10K
#pragma once
#include <iostream>
#include <Core/Types.hpp>
struct GLFWwindow;

namespace UVK
{
    /**
     * @brief The input action struct
     */
    struct InputAction
    {
        InputAction() = default;

        // Used for doing comparing the state
        bool operator==(const uint8_t& st) const;
        bool operator!=(const uint8_t& st) const;

        std::string name{};
        uint16_t keyCode{};
        uint8_t state{};
    };

    /**
     * @brief Generic internal window data
     */
    struct WindowData
    {
        WindowData() = default;

        bool fullscreen = false;
        // path to the window's icon
        std::string image = "../Content/Engine/icon.png";
        std::string name = "Untitled Vulkan Game Engine Editor";
        FVector2 size = FVector2(800, 600);
    };

    /**
     * @brief One of the oldest classes in the entire engine, the Window class
     * serves as an internal window abstraction. Our windowing system is based on GLFW so this class is fairly
     * minimal
     */
    class WindowInternal
    {
    public:
        WindowInternal();
        WindowInternal(const WindowInternal&) = delete;
        void operator=(WindowInternal const&) = delete;

        /**
         * @brief Getter for the internal GLFWwindow
         * @return A pointer to a standard GLFWwindow
         */
        [[nodiscard]] GLFWwindow* getWindow() const;

        bool& getVulkanResized();
    private:
        // Returns the frame-buffer width which in most cases is equal to the Window's internal rendering surface
        // width
        [[nodiscard]] int getBufferWidth() const;

        // Returns the frame-buffer height which in most cases is equal to the Window's internal rendering surface
        // height
        [[nodiscard]] int getBufferHeight() const;

        void setCursorVisibility(bool bIsVisible);
        void setTitle(UVK::String newTitle);

        // Saves all config files including Editor Keybindings, Window settings and Game Keybindings
        void dumpConfig();

        /**
         * @return The internal WindowData struct
         */
        WindowData& data();

        static void saveEditorKeybinds();
        static void saveGameKeybinds();
        void saveWindowSettings() const;

        friend class GLPipeline;
        friend class Renderer;
        friend class GLRenderer;
        friend class VulkanRenderer;
        friend class VKSwapchain;
        friend class Input;
        friend class Editor;
        friend class Pawn;
        friend class Window;
        friend class SettingsManager;
        friend class UIInternal;
        friend class GameInstance;

        [[nodiscard]] FVector2 getLastMousePosition() const;
        [[nodiscard]] FVector2 getCurrentMousePosition() const;
        FVector2 getMousePositionChange();
        FVector2 getScroll();
#ifdef DEVELOPMENT
    public:
        void createWindow();

        void destroyWindow();

    private:
#else
        void createWindow();

        void destroyWindow();
#endif
        /**
         * @brief An array that stores key actions for every key. The size of the array corresponds to the max number
         * of keycodes(listed in Keys.hpp), this way we know that keyArr[Keys::W] will return the state of the W
         * key. The type of the array is the state for the given key index i.e. Pressed, Released, Hold.
         * This state is updated every frame(VulkanRenderer.cpp L38/GLPipeline.cpp L46) when the keyboardInput and
         * Mouse key callbacks are called, which update the state and after the state is updated gameplay classes
         * can read it.
         */
        std::array<uint16_t, 350> keysArr{};
        const std::array<uint16_t, 350>& getKeys();

        // Holds the scroll velocity
        FVector2 scroll{};

        void openConfig();

        // Configures all window callbacks
        void configureCallBacks();

        // Resizes the window's surface
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        // Updates the key state
        static void keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
        // Updates the key state
        static void mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods);
        // Updates mouse cursor position
        static void mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        // Updates the scroll wheel velocity
        static void scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset);

        [[nodiscard]] double getXMousePositionChange();
        [[nodiscard]] double getYMousePositionChange();

        // Internal Window resources
        WindowData resources;

        // Internal GLFW window instance
        GLFWwindow* windowMain = nullptr;

        bool bFirstMove = true;
        bool bVulkanResized = false;

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
        Input() = delete;
        Input(const Input&) = delete;
        void operator=(Input const&) = delete;

        // Given a valid keyboard key from the Keys namespace it will return weather the key was pressed
        static uint8_t getKey(uint16_t key);

        // Input actions are a way of handling key input events by assigning a name to a key.
        // This name and key is stored in a config file, which enables you and your users to rebind key actions
        static const InputAction& getAction(const std::string& name);

        // Returns a list of all input actions
        static std::vector<InputAction>& getActions();

        static FVector2 getMousePositionChange();
        static FVector2 getCurrentMousePosition();
        static FVector2 getLastMousePosition();

        // Returns scroll velocity
        static FVector2 getScroll();
    private:
    };
}