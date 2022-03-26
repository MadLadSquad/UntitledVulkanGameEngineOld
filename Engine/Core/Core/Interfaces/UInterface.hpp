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

        static void addEvent(const std::function<void(void)>& func) noexcept;
        static void addEventImGui(const std::function<void(void)>& func) noexcept;
    };
}