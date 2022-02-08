// WindowInterface.hpp
// Last update 7/2/2022 by Madman10K
#pragma once
#include <Core/Types.hpp>

namespace UVK
{
    class UVK_PUBLIC_API Window
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