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
    // Displays the details panel
    static void display(entt::entity ent)
    {
        ImGui::Begin("Details");
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

        ImGui::End();
    }
}