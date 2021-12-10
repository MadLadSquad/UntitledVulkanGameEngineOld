// SceneHierarchy.cpp
// Last update 29/11/2021 by Madman10K
#include "SceneHierarchy.hpp"
#ifndef PRODUCTION
#include <Core/Actor.hpp>
#include <GameFramework/Actors/ActorManager.hpp>
#include <GameFramework/Components/Components.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <State/StateTracker.hpp>

void SceneHierarchy::destroyEntity(UVK::Actor& selectedEntity)
{
    if (!selectedEntity.has<UVK::CoreComponent>())
        return;
    const auto& a = selectedEntity.get<UVK::CoreComponent>();

    if (a.standart())
    {
        UVK::Transaction transaction =
        {
            .undofunc = [](UVK::TransactionPayload& payload)
            {
                payload.affectedEntity.add<UVK::CoreComponent>() = payload.coreComponent;
                if (payload.bHasComponents[COMPONENT_MESH])
                {
                    payload.affectedEntity.add<UVK::MeshComponent>() = payload.meshComponent;
                }

                if (payload.bHasComponents[COMPONENT_MESH_RAW])
                {
                    payload.affectedEntity.add<UVK::MeshComponentRaw>() = payload.meshComponentRaw;
                }

                if (payload.bHasComponents[COMPONENT_AUDIO])
                {
                    payload.affectedEntity.add<UVK::AudioComponent>() = payload.audioComponent;
                }
            },
            .redofunc = [](UVK::TransactionPayload& payload)
            {
                payload.affectedEntity.clear();
            },
            .transactionPayload =
            {
                .affectedEntity = selectedEntity,
                .coreComponent = a
            }
        };
        if (selectedEntity.has<UVK::MeshComponent>())
        {
            transaction.transactionPayload.meshComponent = selectedEntity.get<UVK::MeshComponent>();
            transaction.transactionPayload.bHasComponents[COMPONENT_MESH] = true;
        }

        if (selectedEntity.has<UVK::MeshComponentRaw>())
        {
            transaction.transactionPayload.meshComponentRaw = selectedEntity.get<UVK::MeshComponentRaw>();
            transaction.transactionPayload.bHasComponents[COMPONENT_MESH_RAW] = true;
        }

        if (selectedEntity.has<UVK::AudioComponent>())
        {
            transaction.transactionPayload.audioComponent = selectedEntity.get<UVK::AudioComponent>();
            transaction.transactionPayload.bHasComponents[COMPONENT_AUDIO] = true;
        }
        UVK::StateTracker::push(transaction);

        selectedEntity.clear();
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
    b.uuid.generate();

    UVK::Transaction transaction =
    {
        .undofunc = [](UVK::TransactionPayload& payload)
        {
            payload.affectedEntity.clear();
        },
        .redofunc = [](UVK::TransactionPayload& payload)
        {
            payload.affectedEntity.add<UVK::CoreComponent>() = payload.coreComponent;
        },
        .transactionPayload =
        {
            .affectedEntity = UVK::Actor(a),
            .coreComponent = b
        }
    };
    UVK::StateTracker::push(transaction);

    entNum++;
}

void SceneHierarchy::display(UVK::Actor& selectedEntity, std::string& entAppend, int& entNum, bool& bShow, const bool& bReset)
{
    static std::vector<std::pair<std::string, size_t>> folders;
    static std::vector<UVK::Actor> selectedEntities;

    if (bReset)
    {
        selectedEntities.clear();
        folders.clear();
    }
    else
    {
        ImGui::Begin("Scene Hierarchy", &bShow, ImGuiWindowFlags_MenuBar);
        ImGui::BeginMenuBar();

        if (ImGui::MenuItem("+ Add Entity##scn"))
            addEntity(entNum);
        if (ImGui::MenuItem("- Destroy Entity##scn") || (UVK::Input::getKey(Keys::Delete) == Keys::KeyPressed && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)))
        {
            if (selectedEntity.valid())
                destroyEntity(selectedEntity);
            for (auto& a : selectedEntities)
                if (a.valid())
                    destroyEntity(a);

            ImGui::SetWindowFocus("Viewport##1");
        }
        if (ImGui::MenuItem("+ Add Folder##scn"));
        ImGui::EndMenuBar();

        size_t i = 0;
        for (auto& a : UVK::ECS::data().view<UVK::CoreComponent>())
        {
            const auto& b = UVK::ECS::data().get<UVK::CoreComponent>(a);

            auto it = std::find(selectedEntities.begin(), selectedEntities.end(), a);
            bool bDrawHighlighted = false;
            if (selectedEntity == a || (it != selectedEntities.end() && *it == a))
            {
                bDrawHighlighted = true; // Needed so that we can pop the colours
                ImGui::PushStyleColor(ImGuiCol_Button, { 0.87f, 0.64f, 0.03, 1.0f });
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.0f, 0.94f, 0.30f, 1.0f });
            }
            else
                ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f, });

            if (ImGui::Button(static_cast<std::string>(b.name + ", " + std::to_string(b.id) + "##" + std::to_string(i)).c_str(), { ImGui::GetContentRegionAvailWidth(), 17.0f }))
            {
                if (UVK::Input::getAction("editor-bind-modifier") == Keys::KeyPressed)
                {
                    if (it != selectedEntities.end() && *it == a)
                        selectedEntities.erase(it);
                    else if (selectedEntity == a)
                        selectedEntity.data() = entt::null;
                    else
                        selectedEntities.emplace_back(a);
                }
                else if (selectedEntity == a)
                {
                    selectedEntity.data() = entt::null;
                    selectedEntities.clear();
                }
                else
                {
                    selectedEntity.data() = a;
                    selectedEntities.clear();
                }
            }

            if (bDrawHighlighted)
            {
                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
            }
            else
                ImGui::PopStyleColor();
        }
        ImGui::End();
    }
}
#endif