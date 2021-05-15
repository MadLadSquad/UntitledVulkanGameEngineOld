// DetailsPanel.hpp
// Last update 15/5/2021 by Madman10K
#pragma once
#include <Core.hpp>

namespace DetailsPanel
{
    // All of this is copied from the Cherno because his styling looks great
    void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);

    void display(entt::entity ent, bool& bShow);
}