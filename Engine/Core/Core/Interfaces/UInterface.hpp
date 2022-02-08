// UInterface.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <functional>
#include <imgui.h>

namespace UVK
{
    class UVK_PUBLIC_API UI
    {
    public:
        UI() = delete;
        UI(const UI&) = delete;
        void operator=(UI const&) = delete;

        static void addEvent(const std::function<void(void)>& func);
        static void addEventImGui(const std::function<void(void)>& func);
    };
}