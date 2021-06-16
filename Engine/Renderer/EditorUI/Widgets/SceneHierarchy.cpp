// SceneHierarchy.cpp
// Last update 15/6/2021 by Madman10K
#include "SceneHierarchy.hpp"

#ifndef PRODUCTION
void SceneHierarchy::destroyEntity(entt::entity& selectedEntity)
{
    if (registry.hasComponent<UVK::MeshComponentRaw>(selectedEntity))
    {
        auto& a = registry.getComponent<UVK::MeshComponentRaw>(selectedEntity);

        a.clearMesh();

        pool.remove<UVK::MeshComponentRaw>(selectedEntity);
    }

    if (registry.hasComponent<UVK::CoreComponent>(selectedEntity))
    {
        auto& a = registry.getComponent<UVK::CoreComponent>(selectedEntity);

        a.name.clear();
        a.id = 0;

        pool.remove<UVK::CoreComponent>(selectedEntity);
    }

    UVK::Registry::destroyActor(selectedEntity);
}

void SceneHierarchy::display(entt::entity &selectedEntity, std::string &entAppend, int &entNum, bool& bShow)
{
    bool bDestroy = false;

    ImGui::Begin("Scene Hierarchy", &bShow, ImGuiWindowFlags_MenuBar);
    ImGui::BeginMenuBar();

    if (ImGui::MenuItem("+ Add Entity##scn"))
    {
        entAppend = std::to_string(entNum);

        registry.createActor("NewEntity" + entAppend);

        entNum++;
    }
    if (ImGui::MenuItem("- Destroy Entity##scn")) bDestroy = true;

    ImGui::EndMenuBar();

    // to be fixed immediately because it's a big performance drain
    pool.each([&](entt::entity ent)
    {
        auto& a = registry.getComponent<UVK::CoreComponent>(ent);

        if (ImGui::Selectable(a.name.c_str()))
        {
            selectedEntity = ent;
        }
    });

    if (pool.valid(selectedEntity))
    {
        if (bDestroy)
        {
            destroyEntity(selectedEntity);
        }
    }

    ImGui::End();
}
#endif