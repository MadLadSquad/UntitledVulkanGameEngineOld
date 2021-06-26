// Window.cpp
// Last update 26/6/2021 by Madman10K
#include "Window.hpp"

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

    if (!bVulkan)
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
    if (bIsFullScreen)
    {
        windowMain = glfwCreateWindow(width, height, name.c_str(), glfwGetPrimaryMonitor(), nullptr);
        logger.consoleLog("Created window", UVK_LOG_TYPE_NOTE);
    }
    else
    {
        windowMain = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        logger.consoleLog("Created window", UVK_LOG_TYPE_NOTE);
    }

    GLFWimage images[1];
    images[0].pixels = stbi_load(image.c_str(), &images[0].width, &images[0].height, nullptr, 4);
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
    glfwSwapInterval(0);

    doCallBacks();

    if (!bVulkan)
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

void UVK::Window::dumpConfig()
{
    YAML::Emitter out;
    out << YAML::BeginMap<< YAML::Key << "image" << YAML::Value << image;
    out << YAML::Key << "width" << YAML::Value << width;
    out << YAML::Key << "height" << YAML::Value << height;
    out << YAML::Key << "fullscreen" << YAML::Value << bIsFullScreen;
    out << YAML::Key << "window-name" << YAML::Value << name;

    std::ofstream fileout("Config/Settings/Window.yaml");
    fileout << out.c_str();
}

void UVK::Window::openConfig()
{
    YAML::Node out;

    bool bValid = true;

    try
    {
        out = YAML::LoadFile("Config/Settings/Window.yaml");
    }
    catch (YAML::BadFile&)
    {
        bValid = false;
    }

    if (bValid)
    {
        if (out["image"])
        {
            image = out["image"].as<std::string>();
        }

        if (out["width"] && out["height"])
        {
            width = out["width"].as<int>();
            height = out["height"].as<int>();
        }

        if (out["fullscreen"])
        {
            bIsFullScreen = out["fullscreen"].as<bool>();
        }

        if (out["window-name"])
        {
            name = out["window-name"].as<std::string>();
        }
    }

    YAML::Node keybinds;
    try
    {
        keybinds = YAML::LoadFile("Config/Settings/Keybinds.yaml");
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
                InGlobals::inputActionList.push_back(action);
            }
        }
    }
}

void UVK::Window::keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    for (auto& a : InGlobals::inputActionList)
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
    for (auto& a : InGlobals::inputActionList)
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
    bVulkan = false;
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

UVK::FVector2 UVK::Input::getLastMousePosition()
{
    return currentWindow.getLastMousePosition();
}

UVK::FVector2 UVK::Input::getCurrentMousePosition()
{
    return currentWindow.getCurrentMousePosition();
}

UVK::FVector2 UVK::Input::getMousePositionChange()
{
    return currentWindow.getMousePositionChange();
}

UVK::FVector2 UVK::Input::getScroll()
{
    return currentWindow.getScroll();
}

const UVK::InputAction& UVK::Input::getAction(const std::string& name)
{
    for (auto& a : InGlobals::inputActionList)
    {
        if (a.name == name)
        {
            return a;
        }
    }

    return *(InputAction*)(nullptr);
}

uint16_t UVK::Input::getKey(uint16_t key)
{
    return currentWindow.getKeys()[key];
}
