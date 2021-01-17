#pragma once
#include <Core.hpp>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <misc/cpp/imgui_stdlib.h>

namespace DetailsPanel
{
    static void Display(entt::entity ent)
    {
        ImGui::Begin("Details");
        if (registry.hasComponent<UVK::CoreComponent>(ent))
        {

            auto& a = registry.getComponent<UVK::CoreComponent>(ent);

            std::string id = std::to_string(a.id);
            ImGui::InputText("name##inputname", &a.name);

            ImGui::InputText("id##inputactoridentifier", &id);
        }

        ImGui::End();
    }
}