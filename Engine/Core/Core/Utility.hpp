#pragma once
#include <Core/Defines.hpp>
#include <iostream>
#include "Types.hpp"

namespace UVK
{
    class UVK_PUBLIC_API UVKGlobal;

    enum ResourcePath
    {
        UVK_RESOURCE_PATH_DIR = 0,
        UVK_RESOURCE_PATH_CONTENT = 1,
        UVK_RESOURCE_PATH_GENERATED = 2,
        UVK_RESOURCE_PATH_SHADER = 2,
        UVK_RESOURCE_PATH_CONFIG_ENGINE = 3,
        UVK_RESOURCE_PATH_CONFIG_SETTINGS = 4
    };

    /**
     * @brief A namespace of useful utility functions
     */
    class UVK_PUBLIC_API Utility
    {
    public:
        Utility() = delete;
        Utility(const Utility&) = delete;
        void operator=(Utility const&) = delete;
        ~Utility() = delete;
        /**
         * @brief Sanitises filepaths
         * @param str the string it sanitises
         * @param bInput is this text inputed by the user or output
         * @return sanitised string
         */
        static void sanitiseFilepath(FString& str, bool bInput) noexcept;

        /**
         * @brief Pass in a string and a key code and it will make the string equal to the corresponding key
         * @param text Reference to the string that will contain the key
         * @param key Const reference to the keycode
         */
        static void keyToText(FString& text, const uint16_t& key, bool bLong) noexcept;
        static FString keyToText(const uint16_t& key, bool bLong) noexcept;
        static UVKGlobal& getGlobal() noexcept;
        static void removeConsole() noexcept;

        static UVK::FString toLower(String str) noexcept;
        static void toLower(FString& str) noexcept;

        static UVK::FString toUpper(String str) noexcept;
        static void toUpper(FString& str) noexcept;
    };

    class UVK_PUBLIC_API Math
    {
    public:
        static void translate(glm::mat4& mat, FVector vt) noexcept;
        static void rotate(glm::mat4& mat, FVector vt) noexcept;
        static void scale(glm::mat4& mat, FVector vt) noexcept;
    };
}