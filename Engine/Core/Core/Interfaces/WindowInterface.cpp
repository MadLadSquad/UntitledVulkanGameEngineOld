#include "WindowInterface.hpp"
#include "Core/Global.hpp"

UVK::FVector2& UVK::Window::windowSize() noexcept
{
    return global.window.data().size;
}

void UVK::Window::setTitle(UVK::String name) noexcept
{
    global.window.setTitle(name);
}

bool& UVK::Window::fullscreen() noexcept
{
    return global.window.data().fullscreen;
}

std::string& UVK::Window::name() noexcept
{
    return global.window.data().name;
}

std::string& UVK::Window::iconLocation() noexcept
{
    return global.window.data().image;
}

void UVK::Window::setCursorVisibility(bool bVisible) noexcept
{
    global.window.setCursorVisibility(bVisible);
    ImGui::GetIO().WantCaptureMouse = bVisible;
}
