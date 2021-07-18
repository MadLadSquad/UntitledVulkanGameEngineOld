// Utility.hpp
// Last update 17/7/2021 by Madman10K
#pragma once
#include <iostream>
#include "Types.hpp"

// A namespace of dangerous stuff that you probably shouldn't touch. It's used to hide design flaws btw.
namespace Internal
{
    // This function is used for opening levels, it's global like that because of our bad design
    inline std::function<void(void)> openFunction;

    // it's global like that because of our bad design
    inline UVK::Level* currentLevel = nullptr;

    inline bool openConfirmation = false;
}

/**
 * @brief A namespace of useful utility functions
 */
namespace Utility
{
    static void toLower(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    static void toUpper(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    }

    /**
     * @brief converts string to lower case
     * @param str string to be converted
     */
    static UVK::String toLowerC_Str(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        return str.c_str();
    }

    static UVK::String toUpperC_Str(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);

        return str.c_str();
    }

    /**
     * @brief Sanitises filepaths
     * @param str the string it sanitises
     * @param bInput is this text inputed by the user or output
     * @return sanitised string
     */
    static void sanitiseFilepath(std::string& str, bool bInput)
    {
        for (auto& a : str)
        {
            if (a == '\\')
            {
                a = '/';
            }

            if (a == ' ')
            {

            }
        }
    }
}