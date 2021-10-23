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
        UI() = delete;
        UI(const UI&) = delete;
        void operator=(UI const&) = delete;

        static void addEvent(const std::function<void(void)>& func);
        static void addEventImGui(const std::function<void(void)>& func);
    };
}