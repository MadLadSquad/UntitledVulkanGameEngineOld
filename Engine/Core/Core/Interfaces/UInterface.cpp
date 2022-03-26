#include "UInterface.hpp"
#include "Core/Global.hpp"

void UVK::UI::addEvent(const std::function<void(void)> &func) noexcept
{
    global.ui.addEvent(func);
}

void UVK::UI::addEventImGui(const std::function<void(void)> &func) noexcept
{
    global.ui.addEventImgui(func);
}
