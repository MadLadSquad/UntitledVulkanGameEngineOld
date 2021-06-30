// SceneHierarchy.hpp
// Last update 30/6/2021 by Madman10K
#pragma once
#include <imgui.h>
#include <iostream>
//#include "../../../GameFramework/Components/Components.hpp"

#ifndef PRODUCTION

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