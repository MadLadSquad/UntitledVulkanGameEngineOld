// Window.cpp
// Last update 2/7/2021 by Madman10K
#include "Window.hpp"
#include <Engine/Core/Core/Global.hpp>

double UVK::Window::getYMousePositionChange()
{
    auto a = (float)offsetY;
    offsetY = 0.0f;

    return a;
}

double UVK::Window::getXMousePositionChange()
{
    auto a = (float)offsetX;
    offsetX = 0.0f;

    return a;
}

void UVK::Window::setTitle(UVK::String newTitle) const
{
    glfwSetWindowTitle(windowMain, newTitle);
}

GLFWwindow* UVK::Window::getWindow() const
{
    return windowMain;
}

UVK::FVector2 UVK::Window::getLastMousePosition() const
{
    return FVector2(lastPosX, lastPosY);
}

UVK::FVector2 UVK::Window::getCurrentMousePosition() const
{
    return FVector2(posX, posY);
}

void UVK::Window::doCallBacks()
{
    glfwSetFramebufferSizeCallback(windowMain, framebufferSizeCallback);
    glfwSetKeyCallback(windowMain, keyboardInputCallback);
    glfwSetCursorPosCallback(windowMain, mouseCursorPositionCallback);
    glfwSetMouseButtonCallback(windowMain, mouseKeyInputCallback);
    glfwSetScrollCallback(windowMain, scrollInputCallback);
}

void UVK::Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void UVK::Window::createWindow()
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
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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

    glfwGetFramebufferSize(windowMain, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(windowMain);
    if (!global.bEditor)
    {
        glfwSwapInterval(0);
    }

    doCallBacks();

    if (!global.bUsesVulkan)
    {
        if (glewInit() != GLEW_OK)
        {
            logger.consoleLog("GLEW initialisation failed!", UVK_LOG_TYPE_ERROR);

            glfwDestroyWindow(windowMain);
            glfwTerminate();
            return;
        }

        glViewport(0, 0, bufferWidth, bufferHeight);
    }

    glfwSetWindowUserPointer(windowMain, this);
}

void UVK::Window::destroyWindow()
{
    glfwDestroyWindow(windowMain);
    glfwTerminate();
}

void UVK::Window::dumpConfig() const
{
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "image" << YAML::Value << resources.image;
    out << YAML::Key << "width" << YAML::Value << resources.size.x;
    out << YAML::Key << "height" << YAML::Value << resources.size.y;
    out << YAML::Key << "fullscreen" << YAML::Value << resources.fullscreen;
    out << YAML::Key << "window-name" << YAML::Value << resources.name;

    std::ofstream fileout("../Config/Settings/Window.yaml");
    fileout << out.c_str();

    saveEditorKeybinds();
    saveGameKeybinds();
}

void UVK::Window::openConfig()
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
            resources.image = out["image"].as<std::string>();
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

void UVK::Window::keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    for (auto& a : global.inputActionList)
    {
        if (a.keyCode == key)
        {
            a.state = action;
        }
    }

    auto* wind = (Window*)glfwGetWindowUserPointer(window);
    wind->keysArr[key] = action;
}

void UVK::Window::mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto* windowInst = static_cast<Window*>(glfwGetWindowUserPointer(window));

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

void UVK::Window::mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods)
{
    for (auto& a : global.inputActionList)
    {
        if (a.keyCode == button)
        {
            a.state = action;
        }
    }

    auto* wind = (Window*)glfwGetWindowUserPointer(window);
    wind->keysArr[button] = action;
}

void UVK::Window::scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto* windowInst = static_cast<Window*>(glfwGetWindowUserPointer(window));

    windowInst->scroll = UVK::FVector2(xoffset, yoffset);
}

const std::array<uint16_t, 350>& UVK::Window::getKeys()
{
    return keysArr;
}

UVK::FVector2 UVK::Window::getScroll()
{
    FVector2 ret = scroll;
    scroll = FVector2(0.0f, 0.0f);
    return ret;
}

UVK::Window::Window()
{
    std::fill(keysArr.begin(), keysArr.end(), false);
}

void UVK::Window::setCursorVisibility(bool bIsVisible)
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

int UVK::Window::getBufferWidth() const
{
    return bufferWidth;
}

UVK::FVector2 UVK::Window::getMousePositionChange()
{
    return FVector2(getXMousePositionChange(), getYMousePositionChange());
}

int UVK::Window::getBufferHeight() const
{
    return bufferHeight;
}

UVK::WindowData& UVK::Window::data()
{
    return resources;
}

void UVK::Window::saveEditorKeybinds()
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

void UVK::Window::saveGameKeybinds()
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

    // trololololololol
    return *(InputAction*)(nullptr);
}

uint16_t UVK::Input::getKey(uint16_t key)
{
    return global.window.getKeys()[key];
}
