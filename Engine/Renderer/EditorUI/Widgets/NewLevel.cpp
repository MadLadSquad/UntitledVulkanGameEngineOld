// NewLevel.cpp
// Last update 30/6/2021 by Madman10K
#include <GL/glew.h>
#include "NewLevel.hpp"
#include "Core/Actor.hpp"

#ifndef PRODUCTION
void NewLevel::display(bool &bShow)
{
    ImGui::Begin("WARNING##new level", &bShow);

    ImGui::Text("Creating a new level will not save any changes to the level you are currently editing!");
    ImGui::Text("If you want to save your changes click Cancel and do so, otherwise you can click Create");

    if (ImGui::Button("Cancel"))
    {
        bShow = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Create##new level"))
    {
        UVK::global.ecs.clear();
        bShow = false;
    }
    ImGui::End();
}
#endif