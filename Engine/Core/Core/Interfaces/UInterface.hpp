// UInterface.hpp
// Last update 17/7/2021 by Madman10K
#pragma once
#include <functional>
#include <imgui.h>

namespace UVK
{
    class UI
    {
    public:
        UI() = default;

        static void addEvent(const std::function<void(void)>& func);
        static void addEventImGui(const std::function<void(void)>& func);
    };
}