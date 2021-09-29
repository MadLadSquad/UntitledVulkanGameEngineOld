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
    void addEntity(int& entNum);
    void destroyEntity(UVK::Actor& selectedEntity);
    void display(UVK::Actor& selectedEntity, std::string& entAppend, int& entNum, bool& bShow);
}
#endif