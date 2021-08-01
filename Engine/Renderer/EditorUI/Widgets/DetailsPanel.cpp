// DetailsPanel.cpp
// Last update 1/8/2021 by Madman10K
#include <GL/glew.h>
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <GameFramework/Components/Components.hpp>
#include "DetailsPanel.hpp"
#include <Core/Actor.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>

#ifndef PRODUCTION
void DetailsPanel::DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue, float columnWidth)
{
    const ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2, nullptr, false);
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

void DetailsPanel::display(UVK::Actor& ent, UVK::Level* lvl, bool& bShow, bool& destroy)
{
    ImGui::Begin("Details", &bShow, ImGuiWindowFlags_MenuBar);

    ImGui::BeginMenuBar();

    if (ImGui::BeginMenu("+ Add Component"))
    {
        if (ImGui::MenuItem("Raw Mesh"))
        {
            if (!ent.has<UVK::MeshComponentRaw>())
            {
                auto& a = ent.add<UVK::MeshComponentRaw>();
            }
        }

        if (ImGui::MenuItem("Mesh"))
        {
            if (!ent.has<UVK::MeshComponent>())
            {
                auto& a = ent.add<UVK::MeshComponent>();
            }
        }

        if (ImGui::MenuItem("Audio"))
        {
            if (!ent.has<UVK::AudioComponent>())
            {
                auto& a = ent.add<UVK::AudioComponent>();

                UVK::AudioSourceData dt;
                dt.location = "test.wav";
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
        if (ImGui::MenuItem("Raw Mesh##rm"))
        {
            if (ent.has<UVK::MeshComponentRaw>())
            {
                ent.remove<UVK::MeshComponentRaw>();
            }
        }

        if (ImGui::MenuItem("Mesh##rm"))
        {
            if (ent.has<UVK::MeshComponent>())
            {
                ent.remove<UVK::MeshComponent>();
            }
        }

        if (ImGui::MenuItem("Audio##rm"))
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

        ImGui::TextWrapped("Name");
        ImGui::SameLine();
        ImGui::InputText("##Name##inputactorname", &a.name);

        auto id = static_cast<int>(a.id);
        ImGui::TextWrapped("ID");
        ImGui::SameLine();
        ImGui::InputInt("##ID##inputactoridentifier", &id);
        if (id == 330 && a.name.find("Editor") == std::string::npos)
            id += 1;
        a.id = id;

        ImGui::TextWrapped("Development Name");
        ImGui::SameLine();
        ImGui::InputText("##Development Name##devname", &a.devName);

        if (a.name == lvl->gameMode->pawn->name && a.id == lvl->gameMode->pawn->id && a.devName == lvl->gameMode->pawn->devName)
        {
            ImGui::Separator();

            static float FOV = lvl->gameMode->pawn->camera.projection().fov();
            static UVK::FVector2 planes = lvl->gameMode->pawn->camera.projection().planes();
            ImGui::TextWrapped("Camera FOV");
            ImGui::SameLine();
            ImGui::SliderFloat("##Camera FOV fov", &FOV, 1.0f, 180.0f);
            ImGui::TextWrapped("Near Plane");
            ImGui::SameLine();
            ImGui::SliderFloat("##Near Plane plane", &planes.x, 0.01f, 10000);
            ImGui::TextWrapped("Far Plane");
            ImGui::SameLine();
            ImGui::SliderFloat("##Far Plane plane", &planes.y, 0.01f, 10000);

            float& ar = lvl->gameMode->pawn->camera.projection().aspectRatio();
            static UVK::FVector2 aspect = UVK::FVector2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

            ImGui::TextWrapped("Aspect Ratio");
            ImGui::SameLine();
            ImGui::DragFloat2("##Aspect Ratio ratio", glm::value_ptr(aspect), 1.0f, 0.01f);

            if ((aspect.x / aspect.y) != ar || FOV != lvl->gameMode->pawn->camera.projection().fov() || planes != lvl->gameMode->pawn->camera.projection().planes())
            {
                lvl->gameMode->pawn->camera.projection().fov() = FOV;
                lvl->gameMode->pawn->camera.projection().planes() = planes;
                ar = aspect.x / aspect.y;
                lvl->gameMode->pawn->camera.projection().recalculateRH();
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
        UVK::AudioSourceData dt = a.data;

        ImGui::TextWrapped("Pitch");
        ImGui::SameLine();
        ImGui::SliderFloat("##Pitchpt", &dt.pitch, 0.5f, 2.0f);

        ImGui::TextWrapped("Gain");
        ImGui::SameLine();
        ImGui::SliderFloat("##Gaingn", &dt.gain, 0.0f, 10.0f);

        ImGui::TextWrapped("Repeat");
        ImGui::SameLine();
        ImGui::Checkbox("##Repeatrt", &dt.bLoop);

        ImGui::TextWrapped("File Location");
        ImGui::SameLine();
        ImGui::InputText("##File Location fl", &dt.location);

        a.data = dt;
        if (ImGui::Button("Play") && !dt.location.empty())
        {
            ent.remove<UVK::AudioComponent>();
            auto& comp = ent.add<UVK::AudioComponent>();
            comp.init(dt);
            comp.play();
        }
        ImGui::SameLine();
        if (ImGui::Button("Resume"))
        {
            a.resume();
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause"))
        {
            a.pause();
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop"))
        {
            a.stop();
        }
        ImGui::SameLine();
        if (ImGui::Button("Replay"))
        {
            a.stop();
            a.play();
        }

        DrawVec3Control("Position", a.data.position, 0.0f, 100.0f);
        DrawVec3Control("Velocity", a.data.velocity, 0.0f, 100.0f);
    }
#endif
    ImGui::End();
}
#endif