// Window.cpp
// Last update 3/27/2021 by Madman10K
#include "Window.hpp"


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

    glewExperimental = GL_TRUE;
    
    //glEnable(GL_DEPTH_TEST); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 16);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);

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
    //glfwSetInputMode(windowMain, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    doCallBacks();

    if (glewInit() != GLEW_OK)
    {
        logger.consoleLog("GLEW initialisation failed!", UVK_LOG_TYPE_ERROR);

        glfwDestroyWindow(windowMain);
        glfwTerminate();
        return;
    }

    glViewport(0, 0, bufferWidth, bufferHeight);
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

    std::ofstream fileout("Config/Settings/Window.yaml");
    fileout << out.c_str();
}

void UVK::Window::openConfig()
{
    auto out = YAML::LoadFile("Config/Settings/Window.yaml");

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

void UVK::Window::keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    auto* windowInst = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    //input.callKeyEvents(key, action);

    if (action == Keys::KeyPressedEvent || action == Keys::KeyRepeatEvent)
    {
        windowInst->keysArr[key] = true;
    }
    else
    {
        windowInst->keysArr[key] = false;
    }
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
   // input.callMouseClickEvents(button, action);
    auto* windowInst = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (action == Keys::KeyPressedEvent || action == Keys::KeyRepeatEvent)
    {
        windowInst->mouseArr[button] = true;
    }
    else
    {
        windowInst->mouseArr[button] = false;
    }
}

void UVK::Window::scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto* windowInst = static_cast<Window*>(glfwGetWindowUserPointer(window));


}
