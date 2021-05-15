// SceneHierarchy.hpp
// Last update 15/5/2021 by Madman10K
#pragma once
#include <imgui.h>
//#include "../../../GameFramework/Components/Components.hpp"
#include "Engine/Core/Core/Registry.hpp"

namespace SceneHierarchy
{
    void destroyEntity(entt::entity& selectedEntity);

    void display(entt::entity& selectedEntity, std::string& entAppend, int& entNum, bool& bShow);
}