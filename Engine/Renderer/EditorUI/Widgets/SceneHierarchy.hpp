// SceneHierarchy.hpp
// Last update 2/7/2021 by Madman10K
#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include <iostream>

namespace UVK
{
    class Actor;
}
/**
 * @brief The scene hierarchy widget creates, manages, destroys entities
 */
namespace SceneHierarchy
{
    struct Folder
    {
        std::string name;
        bool bValid = true; // Saving if a folder is valid for later
        std::vector<UVK::Actor> contents;
    };

    UVK::Actor addEntity(int& entNum);
    void destroyEntity(UVK::Actor& selectedEntity);
    bool display(UVK::Actor& selectedEntity, std::string& entAppend, int& entNum, bool& bShow, const bool& bReset = false);
}
#endif