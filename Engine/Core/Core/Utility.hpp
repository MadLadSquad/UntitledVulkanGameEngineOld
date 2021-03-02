// Utility.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <iostream>

class Utility
{
public:
    static const char* toLower(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        return str.c_str();
    }

    static const char* toHigher(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);

        return str.c_str();
    }

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