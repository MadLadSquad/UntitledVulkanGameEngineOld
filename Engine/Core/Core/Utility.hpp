// Utility.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <iostream>

class Utility
{
public:
    const char* toLower(const char* str)
    {
        auto string = static_cast<std::string>(str);

        std::transform(string.begin(), string.end(), string.begin(), ::tolower);

        return string.c_str();
    }

    const char* toHigher(const char* str)
    {
        auto string = static_cast<std::string>(str);

        std::transform(string.begin(), string.end(), string.begin(), ::toupper);

        return string.c_str();
    }
};