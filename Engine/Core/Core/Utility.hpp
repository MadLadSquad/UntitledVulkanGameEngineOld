// Utility.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include <iostream>

class Utility
{
public:
    /**
     * @brief converts string to lower case
     * @param str string to be converted
     */
    static void toLower(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    /**
     * @brief converts string to upper case
     * @param str string to be converted
     */
    static void toUpper(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    }

    /**
     * @brief converts string to lower case
     * @param str string to be converted
     */
    static const char* toLowerNStr(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        return str.c_str();
    }

    /**
     * @brief converts string to upper case
     * @param str string to be converted
     */
    static const char* toUpperNStr(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);

        return str.c_str();
    }

    /**
     * @brief Sanitises filepaths
     * @param str the string it sanitises
     * @param bInput is this text inputed by the user or output
     * @return
     */
    static const char* sanitiseFilepath(std::string str, bool bInput)
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

        return str.c_str();
    }
};

inline Utility utility;