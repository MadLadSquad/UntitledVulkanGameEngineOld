// Window.cpp
// Last update 29/11/2021 by Madman10K
#include <GL/glew.h>
#include "Window.hpp"
#include <glfw3.h>
#include <yaml.h>
#include <Engine/Core/Core/Global.hpp>
#include <stb/stb_image.h>

double UVK::WindowInternal::getYMousePositionChange()
{
    auto a = (float)offsetY;
    offsetY = 0.0f;

    return a;
}

double UVK::WindowInternal::getXMousePositionChange()
{
    auto a = (float)offsetX;
    offsetX = 0.0f;

    return a;
}

void UVK::WindowInternal::setTitle(UVK::String newTitle)
{
    glfwSetWindowTitle(windowMain, newTitle);
    resources.name = newTitle;
}

GLFWwindow* UVK::WindowInternal::getWindow() const
{
    return windowMain;
}

UVK::FVector2 UVK::WindowInternal::getLastMousePosition() const
{
    return { lastPosX, lastPosY };
}

UVK::FVector2 UVK::WindowInternal::getCurrentMousePosition() const
{
    return { posX, posY };
}

void UVK::WindowInternal::configureCallBacks()
{
    glfwSetFramebufferSizeCallback(windowMain, framebufferSizeCallback);
    glfwSetKeyCallback(windowMain, keyboardInputCallback);
    glfwSetCursorPosCallback(windowMain, mouseCursorPositionCallback);
    glfwSetMouseButtonCallback(windowMain, mouseKeyInputCallback);
    glfwSetScrollCallback(windowMain, scrollInputCallback);
}

void UVK::WindowInternal::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->data().size.x = (float)width;
    windowInst->data().size.y = (float)height;

    if (global.bUsesVulkan)
    {

        //windowInst->bVulkanResized = true;
    }
    else
    {
        glViewport(0, 0, width, height);
    }
}

void UVK::WindowInternal::createWindow()
{
    openConfig();

    if (!glfwInit())
    {
        logger.consoleLog("GLFW initialisation failed!", UVK_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    logger.consoleLog("Setting up the window", UVK_LOG_TYPE_NOTE);

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

    logger.consoleLog("Window settings configured", UVK_LOG_TYPE_NOTE);
    if (resources.fullscreen)
    {
        windowMain = glfwCreateWindow((int)resources.size.x, (int)resources.size.y, resources.name.c_str(), glfwGetPrimaryMonitor(), nullptr);
        logger.consoleLog("Created window", UVK_LOG_TYPE_NOTE);
    }
    else
    {
        windowMain = glfwCreateWindow((int)resources.size.x, (int)resources.size.y, resources.name.c_str(), nullptr, nullptr);
        logger.consoleLog("Created window", UVK_LOG_TYPE_NOTE);
    }

    GLFWimage images[1];
    images[0].pixels = stbi_load(resources.image.c_str(), &images[0].width, &images[0].height, nullptr, 4);
    glfwSetWindowIcon(windowMain, 1, images);
    stbi_image_free(images[0].pixels);

    if (!windowMain)
    {
        logger.consoleLog("GLFW window creation failed!", UVK_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    logger.consoleLog("Window was created successfully", UVK_LOG_TYPE_SUCCESS);

    int tempx = (int)resources.size.x;
    int tempy = (int)resources.size.y;
    glfwGetFramebufferSize(windowMain, &tempx, &tempy);
    resources.size.x = (float)tempx;
    resources.size.y = (float)tempy;

    glfwMakeContextCurrent(windowMain);

#ifndef DEVELOPMENT
    if ((Renderer::getVSync() || global.bEditor) && !global.bUsesVulkan)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }
#else
    glfwSwapInterval(0);
#endif

    configureCallBacks();

    if (!global.bUsesVulkan)
    {
        if (glewInit() != GLEW_OK)
        {
            logger.consoleLog("GLEW initialisation failed!", UVK_LOG_TYPE_ERROR);

            glfwDestroyWindow(windowMain);
            glfwTerminate();
            return;
        }

        glViewport(0, 0, (int)resources.size.x, (int)resources.size.y);
    }

    glfwSetWindowUserPointer(windowMain, this);
}

void UVK::WindowInternal::destroyWindow()
{
    glfwDestroyWindow(windowMain);
    glfwTerminate();

}

void UVK::WindowInternal::dumpConfig()
{
    saveWindowSettings();
    saveEditorKeybinds();
    saveGameKeybinds();
}

void UVK::WindowInternal::openConfig()
{
    YAML::Node out;

    bool bValid = true;

    try
    {
        out = YAML::LoadFile("../Config/Settings/Window.yaml");
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
            keybinds = YAML::LoadFile("../Config/Engine/EditorKeybinds.yaml");
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
                    global.inputActionList.push_back(action);
                }
            }
        }
    }

    YAML::Node keybinds;

    bValid = true;
    try
    {
        keybinds = YAML::LoadFile("../Config/Engine/GameKeybinds.yaml");
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
                global.inputActionList.push_back(action);
            }
        }
    }
}

void UVK::WindowInternal::keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    for (auto& a : global.inputActionList)
    {
        if (a.keyCode == key)
        {
            a.state = action;
        }
    }

    auto* wind = (WindowInternal*)glfwGetWindowUserPointer(window);
    wind->keysArr[key] = action;
}

void UVK::WindowInternal::mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
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

void UVK::WindowInternal::mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods)
{
    for (auto& a : global.inputActionList)
    {
        if (a.keyCode == button)
        {
            a.state = action;
        }
    }

    auto* wind = (WindowInternal*)glfwGetWindowUserPointer(window);
    wind->keysArr[button] = action;
}

void UVK::WindowInternal::scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->scroll = UVK::FVector2(xoffset, yoffset);
}

const std::array<uint16_t, 350>& UVK::WindowInternal::getKeys()
{
    return keysArr;
}

UVK::FVector2 UVK::WindowInternal::getScroll()
{
    FVector2 ret = scroll;
    scroll = FVector2(0.0f, 0.0f);
    return ret;
}

UVK::WindowInternal::WindowInternal()
{
    std::fill(keysArr.begin(), keysArr.end(), false);
}

void UVK::WindowInternal::setCursorVisibility(bool bIsVisible)
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

int UVK::WindowInternal::getBufferWidth() const
{
    return (int)resources.size.x;
}

UVK::FVector2 UVK::WindowInternal::getMousePositionChange()
{
    return { getXMousePositionChange(), getYMousePositionChange() };
}

int UVK::WindowInternal::getBufferHeight() const
{
    return (int)resources.size.y;
}

UVK::WindowData& UVK::WindowInternal::data()
{
    return resources;
}

void UVK::WindowInternal::saveEditorKeybinds()
{
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "bindings" << YAML::BeginSeq;
    for (auto& a : global.inputActionList)
    {
        if (a.name.find("editor-") != std::string::npos)
        {
            out << YAML::BeginMap << YAML::Key << "key" << YAML::Value << a.name;
            out << YAML::Key << "val" << YAML::Value << a.keyCode << YAML::EndMap;
        }
    }

    out << YAML::EndSeq << YAML::EndMap;

    std::ofstream file("../Config/Engine/EditorKeybinds.yaml");
    file << out.c_str();
    file.close();
}

void UVK::WindowInternal::saveGameKeybinds()
{
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "bindings" << YAML::BeginSeq;
    for (auto& a : global.inputActionList)
    {
        if (a.name.find("editor-") == std::string::npos)
        {
            out << YAML::BeginMap << YAML::Key << "key" << YAML::Value << a.name;
            out << YAML::Key << "val" << YAML::Value << a.keyCode << YAML::EndMap;
        }
    }

    out << YAML::EndSeq << YAML::EndMap;

    std::ofstream file("../Config/Engine/GameKeybinds.yaml");
    file << out.c_str();
    file.close();
}

void UVK::WindowInternal::saveWindowSettings() const
{
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "image" << YAML::Value << resources.image;
    out << YAML::Key << "width" << YAML::Value << resources.size.x;
    out << YAML::Key << "height" << YAML::Value << resources.size.y;
    out << YAML::Key << "fullscreen" << YAML::Value << resources.fullscreen;
    out << YAML::Key << "window-name" << YAML::Value << resources.name;

    std::ofstream fileout("../Config/Settings/Window.yaml");
    fileout << out.c_str();
    fileout.close();
}

UVK::FVector2 UVK::Input::getLastMousePosition()
{
    return global.window.getLastMousePosition();
}

UVK::FVector2 UVK::Input::getCurrentMousePosition()
{
    return global.window.getCurrentMousePosition();
}

UVK::FVector2 UVK::Input::getMousePositionChange()
{
    return global.window.getMousePositionChange();
}

UVK::FVector2 UVK::Input::getScroll()
{
    return global.window.getScroll();
}

const UVK::InputAction& UVK::Input::getAction(const std::string& name)
{
    for (auto& a : global.inputActionList)
    {
        if (a.name == name)
        {
            return a;
        }
    }

    logger.consoleLog("Input action with name: ", UVK_LOG_TYPE_ERROR, name, ", does not exist!");
    throw std::runtime_error(" ");
}

uint8_t UVK::Input::getKey(uint16_t key)
{
    return global.window.getKeys()[key];
}

std::vector<UVK::InputAction>& UVK::Input::getActions()
{
    return global.inputActionList;
}

bool UVK::InputAction::operator!=(const uint8_t& st) const
{
    return state != st;
}

bool UVK::InputAction::operator==(const uint8_t& st) const
{
    return state == st;
}