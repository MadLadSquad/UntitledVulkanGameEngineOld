// Utility.hpp
// Last update 27/8/2021 by Madman10K
#pragma once
#include <iostream>
#include "Types.hpp"
#ifdef _WIN32

#else
    #include <sys/resource.h>
#endif

namespace UVK
{
    /**
     * @brief A namespace of useful utility functions
     */
    class Utility
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
        static void sanitiseFilepath(std::string& str, bool bInput);

        /**
         * @brief Pass in a string and a key code and it will make the string equal to the corresponding key
         * @param text Reference to the string that will contain the key
         * @param key Const reference to the keycode
         */
        static void keyToText(std::string& text, const uint16_t& key, bool bLong);
        static std::string keyToText(const uint16_t& key, bool bLong);
    };

    class Math
    {
    public:
        static void translate(glm::mat4& mat, FVector vt);
        static void rotate(glm::mat4& mat, FVector vt);
        static void scale(glm::mat4& mat, FVector vt);
    };
}