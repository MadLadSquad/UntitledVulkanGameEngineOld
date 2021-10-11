// SceneHierarchy.cpp
// Last update 22/9/2021 by Madman10K
#include "SceneHierarchy.hpp"
#ifndef PRODUCTION
#include <Core/Actor.hpp>
#include <GameFramework/Actors/ActorManager.hpp>
#include <GameFramework/Components/Components.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <State/StateTracker.hpp>

void SceneHierarchy::destroyEntity(UVK::Actor& selectedEntity)
{
    const auto& a = selectedEntity.get<UVK::CoreComponent>();

    if (a.id != 330)
    {
        UVK::Transaction transaction =
        {
            .undofunc = [](UVK::Actor& ent, UVK::CoreComponent& coreComponent, UVK::MeshComponentRaw& meshComponentRaw, UVK::MeshComponent& meshComponent, bool* bHasCmp)
            {
                UVK::Actor act(coreComponent.name, coreComponent.id, coreComponent.devName);
                auto& core = act.get<UVK::CoreComponent>();
                core.translation = coreComponent.translation;
                core.rotation = coreComponent.rotation;
                core.scale = coreComponent.scale;

                if (bHasCmp[COMPONENT_MESH])
                {
                    auto& a = act.add<UVK::MeshComponent>();
                    a = meshComponent;
                }

                if (bHasCmp[COMPONENT_MESH_RAW])
                {
                    auto& a = act.add<UVK::MeshComponentRaw>();
                    a = meshComponentRaw;
                }

                ent = act;
            },
            .redofunc = [](UVK::Actor& ent, UVK::CoreComponent& coreComponent, UVK::MeshComponentRaw& meshComponentRaw, UVK::MeshComponent& meshComponent, bool* bHasCmp)
            {
                ent.destroy();
            },
            .coreComponent = a
        };
        if (selectedEntity.has<UVK::MeshComponent>())
        {
            transaction.meshComponent = selectedEntity.get<UVK::MeshComponent>();
            transaction.bHasComponents[COMPONENT_MESH] = true;
        }

        if (selectedEntity.has<UVK::MeshComponentRaw>())
        {
            transaction.meshComponentRaw = selectedEntity.get<UVK::MeshComponentRaw>();
            transaction.bHasComponents[COMPONENT_MESH_RAW] = true;
        }
        UVK::StateTracker::push(transaction);

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

    UVK::Transaction transaction =
    {
        .undofunc = [](UVK::Actor& ent, UVK::CoreComponent&, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
        {
            ent.remove<UVK::CoreComponent>();
            ent.destroy();
        },
        .redofunc = [](UVK::Actor&, UVK::CoreComponent& coreComponent, UVK::MeshComponentRaw&, UVK::MeshComponent&, bool*)
        {
            UVK::Actor act(coreComponent.name, coreComponent.id, coreComponent.devName);
            auto& core = act.get<UVK::CoreComponent>();
            core.translation = coreComponent.translation;
            core.rotation = coreComponent.rotation;
            core.scale = coreComponent.scale;
        },
        .affectedEntity = UVK::Actor(a),
        .coreComponent = b
    };
    UVK::StateTracker::push(transaction);

    entNum++;
}

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