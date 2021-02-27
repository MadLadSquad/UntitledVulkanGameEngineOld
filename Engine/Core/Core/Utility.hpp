// Utility.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <iostream>

class Utility
{
public:
    const char* toLower(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        return str.c_str();
    }

    const char* toHigher(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);

        return str.c_str();
    }

    const char* sanitiseFilepath(std::string& str, bool bInput)
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '\\')
            {
                str[i] = '/';
            }

            if (str[i] == ' ')
            {

            }
        }

        return str.c_str();
    }

};

inline Utility utility;