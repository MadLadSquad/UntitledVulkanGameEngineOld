// SceneHierarchy.cpp
// Last update 26/6/2021 by Madman10K
#include "SceneHierarchy.hpp"
#include <GameFramework/Actors/ActorManager.hpp>
#include <Core/Events/Events.hpp>


void SceneHierarchy::destroyEntity(entt::entity& selectedEntity)
{
    UVK::Registry::destroyActor(selectedEntity);
}

void SceneHierarchy::addEntity(int& entNum)
{
    registry.createActor(static_cast<std::string>("NewEntity" + std::to_string(entNum)).c_str());

    entNum++;
}

#ifndef PRODUCTION

void SceneHierarchy::display(entt::entity &selectedEntity, std::string &entAppend, int &entNum, bool& bShow)
{
    bool bDestroy = false;

    ImGui::Begin("Scene Hierarchy", &bShow, ImGuiWindowFlags_MenuBar);
    ImGui::BeginMenuBar();

    if (ImGui::MenuItem("+ Add Entity##scn"))
    {
        addEntity(entNum);
    }
    if (ImGui::MenuItem("- Destroy Entity##scn")) bDestroy = true;

    ImGui::EndMenuBar();

    // to be fixed immediately because it's a big performance drain
    pool.each([&](entt::entity ent)
    {
        auto& a = registry.getComponent<UVK::CoreComponent>(ent);

        if (ImGui::Selectable(static_cast<std::string>(a.name + ", " + std::to_string(a.id)).c_str()))
        {
            selectedEntity = ent;
        }
    });

    if (bDestroy)
    {
        if (pool.valid(selectedEntity))
        {
            destroyEntity(selectedEntity);
        }
    }

    ImGui::End();
}
#endif