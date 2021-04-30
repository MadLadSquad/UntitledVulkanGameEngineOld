// SceneHierarchy.hpp
// Last update 4/24/2021 by Madman10K
#pragma once
#include <imgui.h>
//#include "../../../GameFramework/Components/Components.hpp"
#include "Engine/Core/Core/Registry.hpp"

namespace SceneHierarchy
{
    static void destroyEntity(entt::entity& selectedEntity)
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

        registry.destroyActor(selectedEntity);
    }

    static void display(entt::entity& selectedEntity, std::string& entAppend, int& entNum)
    {
        bool bDestroy = false;

        ImGui::Begin("Scene Hierarchy");

        if (ImGui::Button("+##add entity"))
        {
            entAppend = std::to_string(entNum);

            registry.createActor("NewEntity" + entAppend);

            entNum++;
        }

        ImGui::SameLine();

        if (ImGui::Button("-##destroy entity"))
        {
            bDestroy = true;
        }

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
}