#pragma once
#include <Core/Defines.hpp>

namespace UVK
{
    class InputAction;

    /**
     * @brief A standard cross-renderer input abstraction
     */
    class UVK_PUBLIC_API Input
    {
    public:
        Input() = delete;
        Input(const Input&) = delete;
        void operator=(Input const&) = delete;

        // Given a valid keyboard key from the Keys namespace it will return weather the key was pressed
        static uint8_t getKey(uint16_t key) noexcept;

        // Input actions are a way of handling key input events by assigning a name to a key.
        // This name and key is stored in a config file, which enables you and your users to rebind key actions
        static const InputAction& getAction(const UVK::FString& name) noexcept;

        // Returns a list of all input actions
        static std::vector<InputAction>& getActions() noexcept;

        static FVector2 getMousePositionChange() noexcept;
        static FVector2 getCurrentMousePosition() noexcept;
        static FVector2 getLastMousePosition() noexcept;

        // Returns scroll velocity
        static FVector2 getScroll() noexcept;
    private:
    };
}