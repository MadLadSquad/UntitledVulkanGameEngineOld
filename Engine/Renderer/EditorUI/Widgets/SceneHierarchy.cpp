// SceneHierarchy.cpp
// Last update 29/11/2021 by Madman10K
#include "SceneHierarchy.hpp"
#ifndef PRODUCTION
#include <Core/Actor.hpp>
#include <GameFramework/Actors/ActorManager.hpp>
#include <GameFramework/Components/Components.hpp>
#include <GameFramework/Components/Components/CoreComponent.hpp>
#include <State/StateTracker.hpp>
#include <cpp/imgui_stdlib.h>

UVK::Actor SceneHierarchy::duplicateEntity(UVK::Actor& currentPopupEntity, const bool& bDrawHighlighted, const bool& nopop)
{
    auto& coreComponent = currentPopupEntity.get<UVK::CoreComponent>();
    UVK::Actor actor(coreComponent.name, coreComponent.id, coreComponent.devName);
    auto& a = actor.add<UVK::CoreComponent>();
    a = coreComponent;
    a.name += "Copy";
    static size_t i = 0;
    UVK::ECS::each([&](UVK::Actor& act){
        if (act.has<UVK::CoreComponent>())
        {
            auto& core = act.get<UVK::CoreComponent>();
            if (core.name == a.name)
            {
                a.name += std::to_string(i);
                i++;
            }
        }
    });
    //if (currentPopupEntity.has<UVK::AudioComponent>())
    //    actor.add<UVK::AudioComponent>() = currentPopupEntity.get<UVK::AudioComponent>();

    // TODO: Add more components
    if (!nopop)
    {
        if (bDrawHighlighted)
            ImGui::PopStyleColor(2);
        else
            ImGui::PopStyleColor();
    }
    return actor;
}

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

UVK::Actor SceneHierarchy::addEntity(int& entNum)
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
    return UVK::Actor(a);
}

bool SceneHierarchy::display(UVK::Actor& selectedEntity, std::string& entAppend, int& entNum, bool& bShow, std::vector<UVK::Editor::Folder>& folders, const bool& bReset)
{
    static std::vector<UVK::Editor::Folder*> selectedFolders;
    static UVK::Editor::Folder* selectedFolder = nullptr;
    static std::vector<UVK::Actor> selectedEntities;
    static bool bDeleteWarning = false;
    static bool bCalledFromPopup = false;
    static UVK::Actor currentPopupEntity;
    static UVK::Editor::Folder* currentPopupFolder = nullptr;
    static std::string* folderName = nullptr;
    bool bReturn = false;

    if (bReset)
    {
        selectedEntities.clear();
        folders.clear();
        selectedFolders.clear();

        selectedFolder = nullptr;

        bDeleteWarning = false;
        bCalledFromPopup = false;

        currentPopupEntity.data() = entt::null;
        currentPopupFolder = nullptr;
    }
    else
    {
        ImGui::Begin("Scene Hierarchy", &bShow, ImGuiWindowFlags_MenuBar);
        ImGui::BeginMenuBar();

        if (ImGui::MenuItem("+ Entity##scn"))
        {
            auto ent = addEntity(entNum);
            if (selectedFolders.empty() && selectedFolder != nullptr)
                selectedFolder->contents.emplace_back(ent);
        }
        if (ImGui::MenuItem("- Entity##scn") || (UVK::Input::getKey(Keys::Delete) == Keys::KeyPressed && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)))
            bDeleteWarning = true;
        if (ImGui::MenuItem("+ Folder##scn"))
        {
            size_t i = 0;
            for (auto& a : folders)
                if (a.name == ("NewFolder" + std::to_string(i)))
                    i++;

            UVK::Editor::Folder fld = {"NewFolder" + std::to_string(i), true, {}};
            folders.emplace_back(fld);
        }
        if (ImGui::MenuItem("- Folder Member"))
        {
            for (auto& f : selectedEntities)
            {
                for (auto& a : folders)
                {
                    if (!a.bValid)
                        continue;
                    for (auto it = a.contents.begin(); it != a.contents.end();)
                    {
                        if (it->valid() && f.valid())
                        {
                            if (*it == f || (selectedEntity.valid() && *it == selectedEntity))
                                it = a.contents.erase(it);
                            else
                                ++it;
                        }
                        else
                            ++it;
                    }
                }
            }
        }
        if (ImGui::MenuItem("+ 2x Duplicate"))
        {
            for (auto& a : selectedEntities)
            {
                if (a.valid())
                {
                    duplicateEntity(a, false);
                }
            }
            if (selectedEntity.valid())
            {
                duplicateEntity(selectedEntity, false);
            }
            return bReturn;
        }
        ImGui::EndMenuBar();

        size_t i = 0;
        for (auto& a : UVK::ECS::data().view<UVK::CoreComponent>())
        {
            const auto& b = UVK::ECS::data().get<UVK::CoreComponent>(a);

            auto it = std::find(selectedEntities.begin(), selectedEntities.end(), a);
            bool bDrawHighlighted = false;

            for (auto& c : folders)
                for (auto& d : c.contents)
                    if (d == a)
                        goto skip; // Some people might hate me for this one but fuck complicated control flow

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

            if (ImGui::BeginDragDropTarget())
            {
                if (const auto payload = ImGui::AcceptDragDropPayload("ENGINE_SH_WIDGET_ENTITY2"))
                {
                    for (auto& f : selectedEntities)
                    {
                        for (auto& folder : folders)
                        {
                            for (auto ff = folder.contents.begin(); ff != folder.contents.end();)
                            {
                                if (*ff == f || (selectedEntity.valid() && selectedEntity == *ff))
                                    ff = folder.contents.erase(ff);
                                else
                                    ++ff;
                            }
                        }
                    }
                }
                ImGui::EndDragDropTarget();
            }

            if (ImGui::IsItemHovered() && UVK::Input::getKey(Keys::MouseButtonRight) == Keys::KeyPressed && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
            {
                ImGui::OpenPopup("##RightClickCategory0");
                currentPopupEntity.data() = a;
            }

            if (currentPopupEntity.data() == a && ImGui::BeginPopup("##RightClickCategory0"))
            {
                if (ImGui::MenuItem("+ New Entity"))
                {
                    auto ent = addEntity(entNum);
                    if (selectedFolders.empty() && selectedFolder != nullptr)
                        selectedFolder->contents.emplace_back(ent);
                }
                if (ImGui::MenuItem("+ New Folder"))
                {
                    size_t j = 0;
                    for (auto& c : folders)
                        if (c.name == ("NewFolder" + std::to_string(j)))
                            i++;

                    UVK::Editor::Folder fld = {"NewFolder" + std::to_string(j), true, {}};
                    folders.emplace_back(fld);
                }
                ImGui::Separator();
                if (ImGui::MenuItem("- Delete Entity"))
                {
                    bDeleteWarning = true;
                    bCalledFromPopup = true;
                }
                if (ImGui::MenuItem("* Remove From Folder"))
                {
                    if (currentPopupEntity.valid())
                    {
                        for (auto& f : folders)
                        {
                            if (!f.bValid)
                                continue;
                            for (auto ff = f.contents.begin(); ff != f.contents.end();)
                            {
                                if (ff->valid())
                                {
                                    if (*ff == currentPopupEntity)
                                        ff = f.contents.erase(ff);
                                    else
                                        ++ff;
                                }
                                else
                                    ++ff;
                            }
                        }
                    }
                }
                if (ImGui::MenuItem("+ 2x Duplicate"))
                {
                    duplicateEntity(currentPopupEntity, bDrawHighlighted, false);
                    return bReturn;
                }
                ImGui::EndPopup();
            }

            if (bDrawHighlighted)
            {
                ImGui::PopStyleColor();
                ImGui::PopStyleColor();
            }
            else
                ImGui::PopStyleColor();

            if (ImGui::BeginDragDropSource())
            {
                UVK::Actor act;
                act.data() = a;
                auto& core = act.get<UVK::CoreComponent>();
                ImGui::Text("Entity: ");
                ImGui::Text("   Name: %s", core.name.c_str());
                ImGui::Text("   ID: %s", std::to_string(core.id).c_str());
                ImGui::Text("   Developer Name: %s", core.devName.c_str());

                ImGui::SetDragDropPayload("ENGINE_SH_WIDGET_ENTITY1", (void*)&a, 1, ImGuiCond_Once);
                ImGui::EndDragDropSource();
            }
skip:; // Semicolon needed to remove compiler error
        }

        i = 0;
        for (auto& a : folders)
        {
            auto folderit = std::find(selectedFolders.begin(), selectedFolders.end(), &a);
            bool bSelected = false;
            if (a.bValid)
            {
                if ((folderit != selectedFolders.end() || &a == selectedFolder))
                {
                    ImGui::PushStyleColor(ImGuiCol_Header, { 0.87f, 0.64f, 0.03, 1.0f });
                    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, { 1.0f, 0.94f, 0.30f, 1.0f });
                    bSelected = true;
                }

                bool header = ImGui::CollapsingHeader((a.name + "##" + std::to_string(a.contents.size()) + std::to_string(i)).c_str());
                if (ImGui::BeginDragDropTarget())
                {
                    if (const auto* payload = ImGui::AcceptDragDropPayload("ENGINE_SH_WIDGET_ENTITY1"))
                    {
                        for (auto& f : selectedEntities)
                            if (f.valid())
                                a.contents.emplace_back(f);
                        if (selectedEntity.valid())
                            a.contents.emplace_back(selectedEntity);
                    }
                    else if (payload = ImGui::AcceptDragDropPayload("ENGINE_SH_WIDGET_ENTITY2"))
                    {
                        for (auto& f : selectedEntities)
                        {
                            if (f.valid())
                            {
                                for (auto& folder : folders)
                                {
                                    for (auto ff = folder.contents.begin(); ff != folder.contents.end();)
                                    {
                                        if (*ff == f || (selectedEntity.valid() && selectedEntity == *ff))
                                            ff = folder.contents.erase(ff);
                                        else
                                            ++ff;
                                    }
                                }
                            }
                        }
                        for (auto& f : selectedEntities)
                            if (f.valid())
                                a.contents.emplace_back(f);
                        if (selectedEntity.valid())
                            a.contents.emplace_back(selectedEntity);
                    }
                    ImGui::EndDragDropTarget();
                }
                if (ImGui::IsItemHovered())
                {
                    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                    {
                        if (UVK::Input::getAction("editor-bind-modifier") == Keys::KeyPressed)
                        {
                            if (bSelected)
                            {
                                if (folderit != selectedFolders.end())
                                    selectedFolders.erase(folderit);
                                else
                                    selectedFolder = nullptr;
                            }
                            else
                                selectedFolders.push_back(&a);
                        }
                        else
                        {
                            selectedFolder = &a;
                            selectedFolders.clear();
                        }
                    }
                    else if ((UVK::Input::getKey(Keys::MouseButtonRight) == Keys::KeyPressed || UVK::Input::getAction("editor-filesystem-rename") == Keys::KeyPressed) && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
                    {
                        ImGui::OpenPopup("##RightClickCategory1");
                        currentPopupFolder = &a;
                        folderName = &currentPopupFolder->name;
                    }
                }

                if (header)
                {
                    size_t j = 0;
                    for (auto& b : a.contents)
                    {
                        auto it = std::find(selectedEntities.begin(), selectedEntities.end(), b);
                        bool bDrawHighlighted = false;
                        if (selectedEntity == b || (it != selectedEntities.end() && *it == b))
                        {
                            bDrawHighlighted = true; // Needed so that we can pop the colours
                            ImGui::PushStyleColor(ImGuiCol_Button, { 0.87f, 0.64f, 0.03, 1.0f });
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.0f, 0.94f, 0.30f, 1.0f });
                        }
                        else
                            ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f, });

                        if (b.has<UVK::CoreComponent>())
                        {
                            const auto& c = b.get<UVK::CoreComponent>();
                            if (ImGui::Button((c.name + ", " + std::to_string(c.id) + "##" + std::to_string(j)).c_str()))
                            {
                                if (UVK::Input::getAction("editor-bind-modifier") == Keys::KeyPressed)
                                {
                                    if (it != selectedEntities.end() && *it == b)
                                        selectedEntities.erase(it);
                                    else if (selectedEntity == b)
                                        selectedEntity.data() = entt::null;
                                    else
                                        selectedEntities.emplace_back(b);
                                }
                                else if (selectedEntity == b)
                                {
                                    selectedEntity.data() = entt::null;
                                    selectedEntities.clear();
                                }
                                else
                                {
                                    selectedEntity = b;
                                    selectedEntities.clear();
                                }
                            }

                            if (ImGui::IsItemHovered() && UVK::Input::getKey(Keys::MouseButtonRight) == Keys::KeyPressed && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
                            {
                                ImGui::OpenPopup("##RightClickCategory0");
                                currentPopupEntity = b;
                            }

                            if (currentPopupEntity == b && ImGui::BeginPopup("##RightClickCategory0"))
                            {
                                if (ImGui::MenuItem("+ New Entity"))
                                {
                                    auto ent = addEntity(entNum);
                                    if (selectedFolders.empty() && selectedFolder != nullptr)
                                        selectedFolder->contents.emplace_back(ent);
                                }
                                if (ImGui::MenuItem("+ New Folder"))
                                {
                                    size_t f = 0;
                                    for (auto& ff : folders)
                                        if (ff.name == ("NewFolder" + std::to_string(f)))
                                            i++;

                                    UVK::Editor::Folder fld = {"NewFolder" + std::to_string(f), true, {}};
                                    folders.emplace_back(fld);
                                }
                                ImGui::Separator();
                                if (ImGui::MenuItem("- Delete Entity"))
                                {
                                    bDeleteWarning = true;
                                    bCalledFromPopup = true;
                                }
                                if (ImGui::MenuItem("* Remove From Folder"))
                                {
                                    if (currentPopupEntity.valid())
                                    {
                                        for (auto& f : folders)
                                        {
                                            if (!f.bValid)
                                                continue;
                                            for (auto ff = f.contents.begin(); ff != f.contents.end();)
                                            {
                                                if (ff->valid())
                                                {
                                                    if (*ff == currentPopupEntity)
                                                        ff = f.contents.erase(ff);
                                                    else
                                                        ++ff;
                                                }
                                                else
                                                    ++ff;
                                            }
                                        }
                                    }
                                }
                                if (ImGui::MenuItem("+ 2x Duplicate"))
                                {
                                    duplicateEntity(currentPopupEntity, bDrawHighlighted, false);
                                    return bReturn;
                                }
                                ImGui::EndPopup();
                            }

                            if (ImGui::BeginDragDropSource())
                            {
                                auto& core = b.get<UVK::CoreComponent>();
                                ImGui::Text("Entity: ");
                                ImGui::Text("   Name: %s", core.name.c_str());
                                ImGui::Text("   ID: %s", std::to_string(core.id).c_str());
                                ImGui::Text("   Developer Name: %s", core.devName.c_str());

                                ImGui::SetDragDropPayload("ENGINE_SH_WIDGET_ENTITY2", (void*)&b.data(), 1, ImGuiCond_Once);
                                ImGui::EndDragDropSource();
                            }
                            j++;
                        }

                        if (bDrawHighlighted)
                            ImGui::PopStyleColor(2);
                        else
                            ImGui::PopStyleColor();
                    }
                }
                if (bSelected)
                    ImGui::PopStyleColor(2);

                if (currentPopupFolder == &a && ImGui::BeginPopup("##RightClickCategory1"))
                {
                    if (ImGui::MenuItem("+ New Entity"))
                    {
                        auto ent = addEntity(entNum);
                        if (selectedFolders.empty() && selectedFolder != nullptr)
                            selectedFolder->contents.emplace_back(ent);
                    }
                    if (ImGui::MenuItem("+ New Folder"))
                    {
                        size_t j = 0;
                        for (auto& c : folders)
                            if (c.name == ("NewFolder" + std::to_string(j)))
                                i++;

                        UVK::Editor::Folder fld = {"NewFolder" + std::to_string(j), true, {}};
                        folders.emplace_back(fld);
                    }
                    ImGui::Separator();
                    if (ImGui::MenuItem("- Delete Folder"))
                    {
                        bDeleteWarning = true;
                        bCalledFromPopup = true;
                        currentPopupEntity.data() = entt::null;
                    }
                    ImGui::Text("Folder Name: ");
                    ImGui::SameLine();

                    if (ImGui::InputText("##NameInputRightClick", folderName) || ImGui::IsItemActive())
                        bReturn = true;

                    ImGui::EndPopup();
                }
                i++;
            }
        }

        if (bDeleteWarning)
        {
            if (!ImGui::IsPopupOpen("Warning##EntityDeletionWarning"))
                ImGui::OpenPopup("Warning##EntityDeletionWarning");
            if (ImGui::BeginPopupModal("Warning##EntityDeletionWarning", &bDeleteWarning))
            {
                ImGui::TextWrapped("You are trying to delete an entity/folder! Deleting most entities can be undone, except for the ones that contain custom components that don't support undo/redo!");
                static bool bAccepted = false;

                ImGui::TextWrapped("I am aware of this!");
                ImGui::SameLine();
                ImGui::Checkbox("##Accepted", &bAccepted);

                if (ImGui::Button("Close##FiledDeletion"))
                    bDeleteWarning = false;
                ImGui::SameLine();
                if (ImGui::Button("Delete##FileDeletion") && bAccepted)
                {
                    if (!bCalledFromPopup)
                    {
                        // Destroy the selected entity
                        if (selectedEntity.valid())
                            destroyEntity(selectedEntity);
                        // Destroy the selected folder and its children
                        if (selectedFolder != nullptr)
                            for (auto& b : selectedFolder->contents)
                                if (b.valid())
                                    destroyEntity(b);
                        // Destroy the other selected entities
                        for (auto& a : selectedEntities)
                            if (a.valid())
                                destroyEntity(a);
                        // Destroy the selected folders and their children
                        for (auto* a : selectedFolders)
                        {
                            if (a->bValid)
                                for (auto& b : a->contents)
                                    if (b.valid())
                                        destroyEntity(b);
                            a->bValid = false;
                        }
                        if (selectedFolder != nullptr)
                        {
                            if (selectedFolder->bValid)
                                for (auto& b : selectedFolder->contents)
                                    if (b.valid())
                                        destroyEntity(b);
                            selectedFolder->bValid = false;
                        }


                        selectedFolder = nullptr;
                        selectedFolders.clear();
                        selectedEntities.clear();
                        selectedEntity.data() = entt::null;
                    }
                    else
                    {
                        if (currentPopupEntity.valid())
                            destroyEntity(currentPopupEntity);
                        else
                        {
                            for (auto& f : currentPopupFolder->contents)
                                destroyEntity(f);
                            for (size_t f = 0; f < folders.size(); f++)
                                if (currentPopupFolder == &folders[f])
                                    folders.erase(folders.begin() + f);
                        }
                    }


                    bDeleteWarning = false;
                    bAccepted = false;
                }

                ImGui::EndPopup();
            }
        }
        // For some reason the neat popups that we tried to add when right-clicking on empty space after everything else is rendered
        // conflict with the other popups, also true for Filesystem.cpp L453
        // TODO: Fix someday
        //if (UVK::Input::getKey(Keys::MouseButtonRight) == Keys::KeyPressed && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) && ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows))
        //    ImGui::OpenPopup("##RightClickCategory2");
        //if (ImGui::BeginPopup("##RightClickCategory2"))
        //{
        //    if (ImGui::MenuItem("New Entity"))
        //    {
        //        auto ent = addEntity(entNum);
        //        if (selectedFolders.empty() && selectedFolder != nullptr)
        //            selectedFolder->contents.emplace_back(ent);
        //    }
        //    if (ImGui::MenuItem("New Folder"))
        //    {
        //        size_t j = 0;
        //        for (auto& c : folders)
        //            if (c.name == ("NewFolder" + std::to_string(j)))
        //                i++;
//      //
        //        Folder fld = {"NewFolder" + std::to_string(j), true, {}};
        //        folders.emplace_back(fld);
        //    }
        //    ImGui::EndPopup();
        //}
        ImGui::End();
    }
    return bReturn;
}
#endif