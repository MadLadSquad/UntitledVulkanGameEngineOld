#include <GL/glew.h>
#include "Window.hpp"
#include <glfw3.h>
#include <yaml.h>
#include <Engine/Core/Core/Global.hpp>
#include <stb/stb_image.h>
#include <Renderer/Vulkan/VulkanRenderer.hpp>

double UVK::WindowInternal::getYMousePositionChange() noexcept
{
    auto a = (float)offsetY;
    offsetY = 0.0f;

    return a;
}

double UVK::WindowInternal::getXMousePositionChange() noexcept
{
    auto a = (float)offsetX;
    offsetX = 0.0f;

    return a;
}

void UVK::WindowInternal::setTitle(UVK::String newTitle) noexcept
{
    glfwSetWindowTitle(windowMain, newTitle);
    resources.name = newTitle;
}

GLFWwindow* UVK::WindowInternal::getWindow() const noexcept
{
    return windowMain;
}

UVK::FVector2 UVK::WindowInternal::getLastMousePosition() const noexcept
{
    return { lastPosX, lastPosY };
}

UVK::FVector2 UVK::WindowInternal::getCurrentMousePosition() const noexcept
{
    return { posX, posY };
}

void UVK::WindowInternal::configureCallBacks() noexcept
{
    glfwSetFramebufferSizeCallback(windowMain, framebufferSizeCallback);
    glfwSetKeyCallback(windowMain, keyboardInputCallback);
    glfwSetCursorPosCallback(windowMain, mouseCursorPositionCallback);
    glfwSetMouseButtonCallback(windowMain, mouseKeyInputCallback);
    glfwSetScrollCallback(windowMain, scrollInputCallback);
}

void UVK::WindowInternal::framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->data().size.x = (float)width;
    windowInst->data().size.y = (float)height;

    // We use this for checking if the window was resized
    windowInst->bResized = true;
}

void UVK::WindowInternal::createWindow() noexcept
{
    openConfig();

    if (!glfwInit())
    {
        Logger::log("GLFW initialisation failed!", UVK_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    Logger::log("Setting up the window", UVK_LOG_TYPE_NOTE);

    if (!global.bUsesVulkan)
    {
        glewExperimental = GL_TRUE;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_SAMPLES, 16);
    }
    else
    {
        // because it's vulkan
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // Vulkan framebuffer resizing is not done
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    }

    Logger::log("Window settings configured", UVK_LOG_TYPE_NOTE);
    if (resources.fullscreen)
    {
        windowMain = glfwCreateWindow((int)resources.size.x, (int)resources.size.y, resources.name.c_str(), glfwGetPrimaryMonitor(), nullptr);
        Logger::log("Created window", UVK_LOG_TYPE_NOTE);
    }
    else
    {
        windowMain = glfwCreateWindow((int)resources.size.x, (int)resources.size.y, resources.name.c_str(), nullptr, nullptr);
        Logger::log("Created window", UVK_LOG_TYPE_NOTE);
    }

    GLFWimage images[1];
    images[0].pixels = stbi_load(resources.image.c_str(), &images[0].width, &images[0].height, nullptr, 4);
    glfwSetWindowIcon(windowMain, 1, images);
    stbi_image_free(images[0].pixels);

    if (!windowMain)
    {
        Logger::log("GLFW window creation failed!", UVK_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    Logger::log("Window was created successfully", UVK_LOG_TYPE_SUCCESS);

    int tempx = (int)resources.size.x;
    int tempy = (int)resources.size.y;
    glfwGetFramebufferSize(windowMain, &tempx, &tempy);
    resources.size.x = (float)tempx;
    resources.size.y = (float)tempy;

    glfwMakeContextCurrent(windowMain);

//#ifndef DEVELOPMENT
//    if ((Renderer::getVSync() || global.bEditor) && !global.bUsesVulkan)
//    {
//        glfwSwapInterval(1);
//    }
//    else
//    {
//        glfwSwapInterval(0);
//    }
//#else
//    glfwSwapInterval(0);
//#endif
    glfwSwapInterval(0);
    configureCallBacks();

    if (!global.bUsesVulkan)
    {
        if (glewInit() != GLEW_OK)
        {
            Logger::log("GLEW initialisation failed!", UVK_LOG_TYPE_ERROR);

            glfwDestroyWindow(windowMain);
            glfwTerminate();
            return;
        }

        glViewport(0, 0, (int)resources.size.x, (int)resources.size.y);
    }

    glfwSetWindowUserPointer(windowMain, this);
}

void UVK::WindowInternal::destroyWindow() noexcept
{
    glfwDestroyWindow(windowMain);
    glfwTerminate();

}

void UVK::WindowInternal::dumpConfig() noexcept
{
    saveWindowSettings();
    saveEditorKeybinds();
    saveGameKeybinds();
}

void UVK::WindowInternal::openConfig() noexcept
{
    YAML::Node out;

    bool bValid = true;

    try
    {
        out = YAML::LoadFile((UVK::FString(UVK_CONFIG_SETTINGS_PATH) + "Window.yaml").c_str());
    }
    catch (YAML::BadFile&)
    {
        bValid = false;
    }

    if (bValid)
    {
        if (out["image"])
        {
            resources.image = "../Content/" + out["image"].as<std::string>();
        }

        if (out["width"] && out["height"])
        {
            resources.size.x = (float)out["width"].as<int>();
            resources.size.y = (float)out["height"].as<int>();
        }

        if (out["fullscreen"])
        {
            resources.fullscreen = out["fullscreen"].as<bool>();
        }

        if (out["window-name"])
        {
            resources.name = out["window-name"].as<std::string>();
        }
    }

    if (global.bEditor)
    {
        YAML::Node keybinds;

        bValid = true;
        try
        {
            keybinds = YAML::LoadFile((UVK::FString(UVK_CONFIG_ENGINE_PATH) + "EditorKeybinds.yaml").c_str());
        }
        catch (YAML::BadFile&)
        {
            bValid = false;
        }

        if (bValid)
        {
            auto binds = keybinds["bindings"];

            if (binds)
            {
                for (const YAML::Node& a : binds)
                {
                    InputAction action{};
                    action.name = a["key"].as<std::string>();
                    action.keyCode = a["val"].as<uint16_t>();
                    global.window.inputActionList.push_back(action);
                }
            }
        }
    }

    YAML::Node keybinds;

    bValid = true;
    try
    {
        keybinds = YAML::LoadFile((UVK::FString(UVK_CONFIG_ENGINE_PATH) + "GameKeybinds.yaml").c_str());
    }
    catch (YAML::BadFile&)
    {
        bValid = false;
    }

    if (bValid)
    {
        auto binds = keybinds["bindings"];

        if (binds)
        {
            for (const YAML::Node& a : binds)
            {
                InputAction action{};
                action.name = a["key"].as<std::string>();
                action.keyCode = a["val"].as<uint16_t>();
                global.window.inputActionList.push_back(action);
            }
        }
    }
}

void UVK::WindowInternal::keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) noexcept
{
    for (auto& a : global.window.inputActionList)
    {
        if (a.keyCode == key)
        {
            a.state = action;
        }
    }

    auto* wind = (WindowInternal*)glfwGetWindowUserPointer(window);
    wind->keysArr[key] = action;
}

void UVK::WindowInternal::mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    if (windowInst->bFirstMove)
    {
        windowInst->lastPosX = xpos;
        windowInst->lastPosY = ypos;
        windowInst->bFirstMove = false;
    }

    windowInst->offsetX = xpos - windowInst->lastPosX;
    windowInst->offsetY = windowInst->lastPosY - ypos;

    if (windowInst->offsetX != 0 && windowInst->offsetY != 0)
    {

    }

    windowInst->lastPosX = xpos;
    windowInst->lastPosY = ypos;
}

void UVK::WindowInternal::mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods) noexcept
{
    for (auto& a : global.window.inputActionList)
    {
        if (a.keyCode == button)
        {
            a.state = action;
        }
    }

    auto* wind = (WindowInternal*)glfwGetWindowUserPointer(window);
    wind->keysArr[button] = action;
}

void UVK::WindowInternal::scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->scroll = UVK::FVector2(xoffset, yoffset);
}

const std::array<uint16_t, 350>& UVK::WindowInternal::getKeys() noexcept
{
    return keysArr;
}

UVK::FVector2 UVK::WindowInternal::getScroll() noexcept
{
    FVector2 ret = scroll;
    scroll = FVector2(0.0f, 0.0f);
    return ret;
}

UVK::WindowInternal::WindowInternal() noexcept
{
    std::fill(keysArr.begin(), keysArr.end(), false);
}

void UVK::WindowInternal::setCursorVisibility(bool bIsVisible) noexcept
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

int UVK::WindowInternal::getBufferWidth() const noexcept
{
    return (int)resources.size.x;
}

UVK::FVector2 UVK::WindowInternal::getMousePositionChange() noexcept
{
    return { getXMousePositionChange(), getYMousePositionChange() };
}

int UVK::WindowInternal::getBufferHeight() const noexcept
{
    return (int)resources.size.y;
}

UVK::WindowData& UVK::WindowInternal::data() noexcept
{
    return resources;
}

void UVK::WindowInternal::saveEditorKeybinds() noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "bindings" << YAML::BeginSeq;
    for (auto& a : global.window.inputActionList)
    {
        if (a.name.find("editor-") != UVK::FString::npos)
        {
            out << YAML::BeginMap << YAML::Key << "key" << YAML::Value << a.name.c_str();
            out << YAML::Key << "val" << YAML::Value << a.keyCode << YAML::EndMap;
        }
    }

    out << YAML::EndSeq << YAML::EndMap;

    std::ofstream file((UVK::FString(UVK_CONFIG_ENGINE_PATH) + "EditorKeybinds.yaml").c_str());
    file << out.c_str();
    file.close();
}

void UVK::WindowInternal::saveGameKeybinds() noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "bindings" << YAML::BeginSeq;
    for (auto& a : global.window.inputActionList)
    {
        if (a.name.find("editor-") == UVK::FString::npos)
        {
            out << YAML::BeginMap << YAML::Key << "key" << YAML::Value << a.name.c_str();
            out << YAML::Key << "val" << YAML::Value << a.keyCode << YAML::EndMap;
        }
    }

    out << YAML::EndSeq << YAML::EndMap;

    std::ofstream file((UVK::FString(UVK_CONFIG_ENGINE_PATH) + "GameKeybinds.yaml").c_str());
    file << out.c_str();
    file.close();
}

void UVK::WindowInternal::saveWindowSettings() const noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "image" << YAML::Value << resources.image.c_str();
    out << YAML::Key << "width" << YAML::Value << resources.size.x;
    out << YAML::Key << "height" << YAML::Value << resources.size.y;
    out << YAML::Key << "fullscreen" << YAML::Value << resources.fullscreen;
    out << YAML::Key << "window-name" << YAML::Value << resources.name.c_str();

    std::ofstream fileout((UVK::FString(UVK_CONFIG_SETTINGS_PATH) + "Window.yaml").c_str());
    fileout << out.c_str();
    fileout.close();
}

bool& UVK::WindowInternal::resized() noexcept
{
    return bResized;
}

bool UVK::InputAction::operator!=(const uint8_t& st) const noexcept
{
    return state != st;
}

bool UVK::InputAction::operator==(const uint8_t& st) const noexcept
{
    return state == st;
}