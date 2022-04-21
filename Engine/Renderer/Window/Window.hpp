#pragma once
#include <iostream>
#include <Core/Types.hpp>
struct GLFWwindow;

namespace UVK
{
    struct InternalRendererComponents;
    /**
     * @brief The input action struct
     */
    struct UVK_PUBLIC_API InputAction
    {
        InputAction() = default;

        // Used for doing comparing the state
        bool operator==(const uint8_t& st) const noexcept;
        bool operator!=(const uint8_t& st) const noexcept;

        std::string name{};
        uint16_t keyCode{};
        uint8_t state{};
    };

    /**
     * @brief Generic internal window data
     */
    struct UVK_PUBLIC_API WindowData
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
    class UVK_PUBLIC_API WindowInternal
    {
    public:
        WindowInternal() noexcept;
        WindowInternal(const WindowInternal&) = delete;
        void operator=(WindowInternal const&) = delete;

        /**
         * @brief Getter for the internal GLFWwindow
         * @return A pointer to a standard GLFWwindow
         */
        [[nodiscard]] GLFWwindow* getWindow() const noexcept;
        bool& resized() noexcept;
    private:
        // Returns the frame-buffer width which in most cases is equal to the Window's internal rendering surface
        // width
        [[nodiscard]] int getBufferWidth() const noexcept;

        // Returns the frame-buffer height which in most cases is equal to the Window's internal rendering surface
        // height
        [[nodiscard]] int getBufferHeight() const noexcept;

        void setCursorVisibility(bool bIsVisible) noexcept;
        void setTitle(UVK::String newTitle) noexcept;

        // Saves all config files including Editor Keybindings, Window settings and Game Keybindings
        void dumpConfig() noexcept;

        /**
         * @return The internal WindowData struct
         */
        WindowData& data() noexcept;

        static void saveEditorKeybinds() noexcept;
        static void saveGameKeybinds() noexcept;
        void saveWindowSettings() const noexcept;

        friend class GLPipeline;
        friend class Renderer;
        friend class GLRenderer;
        friend class VulkanRenderer;
        friend class Swapchain;
        friend class Input;
        friend class Editor;
        friend class Pawn;
        friend class Window;
        friend class SettingsManager;
        friend class UIInternal;
        friend class GameInstance;

        [[nodiscard]] FVector2 getLastMousePosition() const noexcept;
        [[nodiscard]] FVector2 getCurrentMousePosition() const noexcept;
        FVector2 getMousePositionChange() noexcept;
        FVector2 getScroll() noexcept;
#ifdef DEVELOPMENT
    public:
        void createWindow() noexcept;

        void destroyWindow() noexcept;

    private:
#else
        void createWindow() noexcept;

        void destroyWindow() noexcept;
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
        const std::array<uint16_t, 350>& getKeys() noexcept;

        // Holds the scroll velocity
        FVector2 scroll{};

        void openConfig() noexcept;

        // Configures all window callbacks
        void configureCallBacks() noexcept;

        // Resizes the window's surface
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept;
        // Updates the key state
        static void keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) noexcept;
        // Updates the key state
        static void mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods) noexcept;
        // Updates mouse cursor position
        static void mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept;
        // Updates the scroll wheel velocity
        static void scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept;

        [[nodiscard]] double getXMousePositionChange() noexcept;
        [[nodiscard]] double getYMousePositionChange() noexcept;

        // Internal Window resources
        WindowData resources;

        // Internal GLFW window instance
        GLFWwindow* windowMain = nullptr;

        InternalRendererComponents* renderer = nullptr;

        bool bFirstMove = true;
        bool bResized = false;

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
    class UVK_PUBLIC_API Input
    {
    public:
        Input() = delete;
        Input(const Input&) = delete;
        void operator=(Input const&) = delete;

        // Given a valid keyboard key from the Keys namespace it will return weather the key was pressed
        static uint8_t getKey(uint16_t key) noexcept;

        // Input actions are a way of handling key input events by assigning a name to a key.
        // This name and key is stored in a config file, which enables you and your users to rebind key actions
        static const InputAction& getAction(const std::string& name) noexcept;

        // Returns a list of all input actions
        static std::vector<InputAction>& getActions() noexcept;

        static FVector2 getMousePositionChange() noexcept;
        static FVector2 getCurrentMousePosition() noexcept;
        static FVector2 getLastMousePosition() noexcept;

        // Returns scroll velocity
        static FVector2 getScroll() noexcept;
    private:
    };
}