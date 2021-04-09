// DetailsPanel.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

namespace DetailsPanel
{
    inline int selectedItem = 0;

    // All of this is copied from the Cherno because his styling looks great
    static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
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
        //ImGui::PushStyleVar(ImGuiStyleVar_)

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

    static void DrawVec4Control(const std::string& label, glm::vec4& values, float resetValue = 0.0f, float columnWidth = 100.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushItemWidth(32);
        ImGui::PushItemWidth(32);
        ImGui::PushItemWidth(32);
        ImGui::PushItemWidth(32);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
        //ImGui::PushStyleVar(ImGuiStyleVar_)

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
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.96f, 0.46f, 0.1f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.96f, 0.55f, 0.25f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.96f, 0.46f, 0.1f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("W", buttonSize))
            values.w = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##W", &values.w, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();


        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    // Displays the details panel
    static void display(entt::entity ent)
    {
        ImGui::Begin("Details");

        ImGui::Button("+##ADDCMP");

        if (registry.hasComponent<UVK::CoreComponent>(ent))
        {

            auto& a = registry.getComponent<UVK::CoreComponent>(ent);

            std::string id = std::to_string(a.id);
            ImGui::InputText("name##inputname", &a.name);

            ImGui::InputText("id##inputactoridentifier", &id);
        }

        if (registry.hasComponent<UVK::AudioComponent2D>(ent))
        {
            auto& a = registry.getComponent<UVK::AudioComponent2D>(ent);

            auto rep = a.getRepeat();
            auto pitch = a.getPitch();
            auto gain = a.getGain();
            std::string loc = a.getLocation();

            ImGui::Checkbox("Repeat audio?##a", &rep);
            ImGui::SliderFloat("Pitch##2d", &pitch, 0.5f, 2.0f);
            ImGui::SliderFloat("Gain##2d", &gain, 0.0f, 10.0f);
            ImGui::InputText("Audio location##2d", &loc);
        }

        if (registry.hasComponent<UVK::MeshComponentRaw>(ent))
        {

            ImGui::BeginTabBar("");

            auto& a = registry.getComponent<UVK::MeshComponentRaw>(ent);

            DrawVec3Control("Translation", a.translation, 0.0f, 100.0f);

            glm::vec3 rotation = glm::degrees(a.rotation);

            DrawVec3Control("Rotation", rotation, 0.0f, 100.0f);

            a.rotation = glm::radians(rotation);

            DrawVec3Control("Scale", a.scale, 1.0f, 100.0f);
            /*float translation[3] = { a.translation.x, a.translation.y, a.translation.z };
            float rotation[4] = { a.rotation.x, a.rotation.y, a.rotation.z, a.rotation.w };
            float scale[3] = { a.scale.x, a.scale.y, a.scale.z };

            ImGui::DragFloat3("Translation##drag", translation, 0.01f);
            ImGui::DragFloat4("Rotation##drag", rotation, 0.01f);
            ImGui::DragFloat3("Scale##drag", scale, 0.01f);

            a.translation = glm::vec3(translation[0], translation[1], translation[2]);
            a.rotation = glm::vec4(rotation[0], rotation[1], rotation[2], rotation[3]);
            a.scale = glm::vec3(scale[0], scale[1], scale[2]);
             */
        }

        ImGui::End();
    }


}