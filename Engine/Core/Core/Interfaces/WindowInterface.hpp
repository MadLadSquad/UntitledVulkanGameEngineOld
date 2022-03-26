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

        static void setTitle(UVK::String name) noexcept;
        static void setCursorVisibility(bool bVisible) noexcept;

        static FVector2& windowSize() noexcept;
        static bool& fullscreen() noexcept;

        static std::string& name() noexcept;
        static std::string& iconLocation() noexcept;
    };
}