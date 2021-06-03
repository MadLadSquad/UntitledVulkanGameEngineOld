// DetailsPanel.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <Core.hpp>

/**
 * @brief Displays the Details Panel which is used to add, manipulate and remove components from selected entities
 */
namespace DetailsPanel
{
    // All of this is copied from the Cherno because his styling looks great
    void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);

    void display(entt::entity& ent, bool& bShow, bool& destroy);
}