// Utility.hpp
// Last update 27/8/2021 by Madman10K
#pragma once
#include <iostream>
#include "Types.hpp"

/**
 * @brief A namespace of useful utility functions
 */
namespace Utility
{
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