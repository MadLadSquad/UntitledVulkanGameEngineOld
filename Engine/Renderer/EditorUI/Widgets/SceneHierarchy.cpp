// SceneHierarchy.cpp
// Last update 22/9/2021 by Madman10K
#include "SceneHierarchy.hpp"
#include <Core/Actor.hpp>
#include <GameFramework/Actors/ActorManager.hpp>
#include <GameFramework/Components/Components.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>

void SceneHierarchy::destroyEntity(UVK::Actor& selectedEntity)
{
    const auto& a = selectedEntity.get<UVK::CoreComponent>();

    if (a.id != 330)
    {
        selectedEntity.destroy();
    }
}

void SceneHierarchy::addEntity(int& entNum)
{
    //registry.createActor(static_cast<std::string>("NewEntity" + std::to_string(entNum)).c_str());
    //UVK::Actor actor(static_cast<std::string>("NewEntity" + std::to_string(entNum)), 0, "a");
    const auto a = UVK::ECS::data().create();
    auto& b = UVK::ECS::data().emplace<UVK::CoreComponent>(a);
    b.name = "NewEntity" + std::to_string(entNum);
    b.id = 0;
    b.devName = "a";

    entNum++;
}

#ifndef PRODUCTION

void SceneHierarchy::display(UVK::Actor& selectedEntity, std::string &entAppend, int &entNum, bool& bShow)
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
    UVK::ECS::data().each([&](entt::entity ent)
    {
        const auto& a = UVK::ECS::data().get<UVK::CoreComponent>(ent);

        if (ImGui::Selectable(static_cast<std::string>(a.name + ", " + std::to_string(a.id)).c_str()))
        {
            if (UVK::ECS::data().valid(ent))
                selectedEntity.data() = ent;
        }
    });

    if (bDestroy && UVK::ECS::data().valid(selectedEntity.data()))
    {
        destroyEntity(selectedEntity);
    }

    ImGui::End();
}
#endif