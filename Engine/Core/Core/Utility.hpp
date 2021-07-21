// Utility.hpp
// Last update 21/7/2021 by Madman10K
#pragma once
#include <iostream>
#include "Types.hpp"

// Due to the bad way in which our scene switching system works this namespace is needed. The open level design
// may be the only hard to debug point of the engine
//
// The problem: Since the Level class is included in Global.hpp we cannot include Global.hpp into Level
// This proved to be a big problem since the open function was transitioned to a template(can only be defined in headers)
//
// The solution: Provide this namespace of global variables to supplement the Level class
//
// The variables:
// This function pointer is responsible for carrying an open level callback
// Because of our design, the gameplay and engine classes aren't directly aware of their state which leeds to this
// callback being used. A gameplay class would call open level in the tick, this will make the function
// point to a valid location and the openConfirmation flag will be enabled. The global class has the "finalizeOpening"
// function and this function is called every frame in GLPipeline,
// when running a normally finalizeOpening will do nothing but in the scenario where a level was declared
// to be opened in the previous frame, it will proceed to free the memory of currentLevel, and call the openFunction,
// which then leads to the gameplay begin events being called and the openConfirmation flag being set to false,
// getting the rendering state back to normal. Now your question may be something along the lines of "Why do we need
// currentLevel?", it's needed because we cannot include global into our Level class, which leads to us having to make
// this pointer point to a class then copy the pointer to the UVKGlobal's current level.
//
// I hope that this helped anyone debugging or exploring the codebase
namespace Internal
{
    inline std::function<void(void)> openFunction;
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