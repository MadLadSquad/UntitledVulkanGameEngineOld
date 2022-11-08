#include "InputInterface.hpp"
#include <Core/Global.hpp>

UVK::FVector2 UVK::Input::getLastMousePosition() noexcept
{
    return global.window.getLastMousePosition();
}

UVK::FVector2 UVK::Input::getCurrentMousePosition() noexcept
{
    return global.window.getCurrentMousePosition();
}

UVK::FVector2 UVK::Input::getMousePositionChange() noexcept
{
    return global.window.getMousePositionChange();
}

UVK::FVector2 UVK::Input::getScroll() noexcept
{
    return global.window.getScroll();
}

const UVK::InputAction& UVK::Input::getAction(const UVK::FString& name) noexcept
{
    for (auto& a : global.window.inputActionList)
        if (a.name == name)
            return a;

    Logger::log("Input action with name: ", UVK_LOG_TYPE_ERROR, name, ", does not exist!");
    std::terminate();
}

uint8_t UVK::Input::getKey(uint16_t key) noexcept
{
    return global.window.getKeys()[key];
}

std::vector<UVK::InputAction>& UVK::Input::getActions() noexcept
{
    return global.window.inputActionList;
}