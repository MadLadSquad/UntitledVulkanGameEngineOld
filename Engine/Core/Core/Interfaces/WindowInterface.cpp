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

UVK::FString& UVK::Window::name() noexcept
{
    return global.window.data().name;
}

UVK::FString& UVK::Window::iconLocation() noexcept
{
    return global.window.data().image;
}

void UVK::Window::setCursorVisibility(bool bVisible) noexcept
{
    global.window.setCursorVisibility(bVisible);
    //ImGui::GetIO().WantCaptureMouse = bVisible;
}

float UVK::Window::aspectRatio() noexcept
{
    return windowSize().x / windowSize().y;
}
