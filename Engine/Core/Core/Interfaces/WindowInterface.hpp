#pragma once
#include <Core/Types.hpp>
#include <Core/Defines.hpp>

namespace UVK
{
    // A class to provide easy integration with the windowing system
    class UVK_PUBLIC_API Window
    {
    public:
        Window() = delete;
        Window(const Window&) = delete;
        void operator=(Window const&) = delete;

        static void setTitle(UVK::String name) noexcept;
        static void setCursorVisibility(bool bVisible) noexcept;

        static float aspectRatio() noexcept;

        static FVector2& windowSize() noexcept;
        static bool& fullscreen() noexcept;

        static FString& name() noexcept;
        static FString& iconLocation() noexcept;
    };
}