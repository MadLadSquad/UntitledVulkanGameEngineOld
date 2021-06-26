// SceneHierarchy.hpp
// Last update 26/6/2021 by Madman10K
#pragma once
#include <imgui.h>
//#include "../../../GameFramework/Components/Components.hpp"
#include "Engine/Core/Core/Registry.hpp"

#ifndef PRODUCTION
/**
 * @brief The scene hierarchy widget creates, manages, destroys entities
 */
namespace SceneHierarchy
{
    void addEntity(int& entNum);

    void destroyEntity(entt::entity& selectedEntity);

    void display(entt::entity& selectedEntity, std::string& entAppend, int& entNum, bool& bShow);
}
#endif