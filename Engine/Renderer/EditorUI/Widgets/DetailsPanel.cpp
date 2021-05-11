// DetailsPanel.cpp
// Last update 5/5/2021 by Madman10K
#include <Core/Registry.hpp>
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include "DetailsPanel.hpp"

void DetailsPanel::DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue, float columnWidth)
{
    ImGuiIO& io = ImGui::GetIO();
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

void DetailsPanel::display(entt::entity ent)
{
    ImGui::Begin("Details", nullptr);

    ImGui::Button("+##ADDCMP");

    if (registry.hasComponent<UVK::CoreComponent>(ent))
    {

        auto& a = registry.getComponent<UVK::CoreComponent>(ent);

        std::string id = std::to_string(a.id);
        ImGui::InputText("name##inputname", &a.name);

        ImGui::InputText("id##inputactoridentifier", &id);
    }

    if (registry.hasComponent<UVK::MeshComponentRaw>(ent))
    {
        auto& a = registry.getComponent<UVK::MeshComponentRaw>(ent);

        DrawVec3Control("Translation", a.translation, 0.0f, 100.0f);
        glm::vec3 rotation = glm::degrees(a.rotation);
        DrawVec3Control("Rotation", rotation, 0.0f, 100.0f);
        a.rotation = glm::radians(rotation);
        DrawVec3Control("Scale", a.scale, 1.0f, 100.0f);
    }
    ImGui::End();
}