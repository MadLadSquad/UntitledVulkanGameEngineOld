// WindowInterface.hpp
// Last update 17/7/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace UVK
{
    class Window
    {
    public:
        Window() = delete;
        Window(const Window&) = delete;
        void operator=(Window const&) = delete;

        static void setTitle(UVK::String name);
        static void setCursorVisibility(bool bVisible);

        static FVector2& windowSize();
        static bool& fullscreen();

        static std::string& name();
        static std::string& iconLocation();
    };
}