// WindowInterface.cpp
// Last update 1/8/2021 by Madman10K
#include <GL/glew.h>
#include "WindowInterface.hpp"
#include "Core/Global.hpp"

UVK::FVector2& UVK::Window::windowSize()
{
    return global.window.data().size;
}

void UVK::Window::setTitle(UVK::String name)
{
    global.window.setTitle(name);
}

bool& UVK::Window::fullscreen()
{
    return global.window.data().fullscreen;
}

std::string& UVK::Window::name()
{
    return global.window.data().name;
}

std::string& UVK::Window::iconLocation()
{
    return global.window.data().image;
}

void UVK::Window::setCursorVisibility(bool bVisible)
{
    global.window.setCursorVisibility(bVisible);
}
