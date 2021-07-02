// DetailsPanel.cpp
// Last update 30/6/2021 by Madman10K
#include <GL/glew.h>
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <GameFramework/Components/Components.hpp>
#include "DetailsPanel.hpp"
#include <Core/Actor.hpp>

#ifndef PRODUCTION
void DetailsPanel::DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue, float columnWidth)
{
    const ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushItemWidth(50);
    ImGui::PushItemWidth(50);
    ImGui::PushItemWidth(50);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize))
        values.x = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize))
        values.y = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize))
        values.z = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
}

void DetailsPanel::display(UVK::Actor& ent, UVK::Level* lvl, bool& bShow, bool& destroy, UVK::Texture& insert, const std::string& cpFileLoc)
{
    ImGui::Begin("Details", &bShow, ImGuiWindowFlags_MenuBar);

    ImGui::BeginMenuBar();

    if (ImGui::BeginMenu("+ Add Component"))
    {
        if (ImGui::Button("Raw Mesh"))
        {
            if (!ent.has<UVK::MeshComponentRaw>())
            {
                auto& a = ent.add<UVK::MeshComponentRaw>();
            }
        }

        if (ImGui::Button("Mesh"))
        {
            if (!ent.has<UVK::MeshComponent>())
            {
                auto& a = ent.add<UVK::MeshComponent>();
            }
        }

        if (ImGui::Button("Audio"))
        {
            if (!ent.has<UVK::AudioComponent>())
            {
                auto& a = ent.add<UVK::AudioComponent>();

                UVK::AudioSourceData dt;
                dt.location = "and.wav";
                dt.velocity = UVK::FVector(0.0f, 0.0f, 0.0f);
                dt.position = UVK::FVector(0.0f, 0.0f, 0.0f);
                dt.bLoop = false;
                dt.gain = 1.0f;
                dt.pitch = 1.0f;

                a.init(dt);
            }
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("- Remove Component"))
    {
        if (ImGui::Button("Raw Mesh##rm"))
        {
            if (ent.has<UVK::MeshComponentRaw>())
            {
                ent.remove<UVK::MeshComponentRaw>();
            }
        }

        if (ImGui::Button("Mesh##rm"))
        {
            if (ent.has<UVK::MeshComponent>())
            {
                ent.remove<UVK::MeshComponent>();
            }
        }

        if (ImGui::Button("Audio##rm"))
        {
            if (ent.has<UVK::AudioComponent>())
            {
                ent.remove<UVK::AudioComponent>();
            }
        }

        ImGui::EndMenu();
    }
    ImGui::EndMenuBar();

    if (ent.has<UVK::CoreComponent>())
    {
        auto& a = ent.get<UVK::CoreComponent>();

        std::string id = std::to_string(a.id);
        ImGui::InputText("Name##inputactorname", &a.name);
        ImGui::SameLine();
        if (ImGui::ImageButton((void*)(intptr_t)insert.getImage(), ImVec2(10.0f, 10.0f)))
        {
            a.name = cpFileLoc;
        }

        ImGui::InputText("ID##inputactoridentifier", &id);
        ImGui::SameLine();
        if (ImGui::ImageButton((void*)(intptr_t)insert.getImage(), ImVec2(10.0f, 10.0f)))
        {
            id = cpFileLoc;
        }

        ImGui::InputText("Development Name##devname", &a.devName);
        ImGui::SameLine();
        if (ImGui::ImageButton((void*)(intptr_t)insert.getImage(), ImVec2(10.0f, 10.0f)))
        {
            a.devName = cpFileLoc;
        }

        if (a.name == lvl->gameMode->pawn->name && a.id == lvl->gameMode->pawn->id && a.devName == lvl->gameMode->pawn->devName)
        {
            ImGui::Separator();

            static float FOV = lvl->gameMode->pawn->camera.getProjection().getFOV();
            static UVK::FVector2 planes = lvl->gameMode->pawn->camera.getProjection().getPlanes();
            ImGui::SliderFloat("Camera FOV", &FOV, 1.0f, 180.0f);
            ImGui::SliderFloat("Near Plane", &planes.x, 0.01f, 10000);
            ImGui::SliderFloat("Far Plane", &planes.y, 0.01f, 10000);

            float& ar = lvl->gameMode->pawn->camera.getProjection().getAspectRatio();
            static UVK::FVector2 aspect = UVK::FVector2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

            ImGui::DragFloat2("Aspect Ratio", glm::value_ptr(aspect), 1.0f, 0.01f);

            if ((aspect.x / aspect.y) != ar || FOV != lvl->gameMode->pawn->camera.getProjection().getFOV() || planes != lvl->gameMode->pawn->camera.getProjection().getPlanes())
            {
                lvl->gameMode->pawn->camera.getProjection().getFOV() = FOV;
                lvl->gameMode->pawn->camera.getProjection().getPlanes() = planes;
                ar = aspect.x / aspect.y;
                lvl->gameMode->pawn->camera.getProjection().recalculateRH();
            }
        }
    }

    if (ent.has<UVK::MeshComponentRaw>())
    {
        ImGui::Separator();

        auto& a = ent.get<UVK::MeshComponentRaw>();

        DrawVec3Control("Translation", a.translation, 0.0f, 100.0f);
        glm::vec3 rotation = glm::degrees(a.rotation);
        DrawVec3Control("Rotation", rotation, 0.0f, 100.0f);
        a.rotation = glm::radians(rotation);
        DrawVec3Control("Scale", a.scale, 1.0f, 100.0f);
    }

#ifndef __MINGW32__
    if (ent.has<UVK::AudioComponent>())
    {
        ImGui::Separator();
        auto& a = ent.get<UVK::AudioComponent>();

        ImGui::SliderFloat("Pitch", &a.data.pitch, 0.5f, 2.0f);
        ImGui::SliderFloat("Gain", &a.data.gain, 0.0f, 10.0f);
        ImGui::Checkbox("Repeat", &a.data.bLoop);
        ImGui::InputText("File Location", &a.data.location);
        ImGui::SameLine();
        if (ImGui::ImageButton((void*)(intptr_t)insert.getImage(), ImVec2(10.1f, 10.1f)))
        {
            std::cout << "true" << std::endl;
            a.data.location = cpFileLoc;
        }
        DrawVec3Control("Position", a.data.position, 0.0f, 100.0f);
        DrawVec3Control("Velocity", a.data.velocity, 0.0f, 100.0f);
    }
#endif
    ImGui::End();
}
#endif