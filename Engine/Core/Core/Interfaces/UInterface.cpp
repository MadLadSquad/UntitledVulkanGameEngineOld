// UInterface.cpp
// Last update 1/8/2021 by Madman10K
#include <GL/glew.h>
#include "UInterface.hpp"
#include "Core/Global.hpp"

void UVK::UI::addEvent(const std::function<void(void)> &func)
{
    global.ui.addEvent(func);
}

void UVK::UI::addEventImGui(const std::function<void(void)> &func)
{
    global.ui.addEventImgui(func);
}
