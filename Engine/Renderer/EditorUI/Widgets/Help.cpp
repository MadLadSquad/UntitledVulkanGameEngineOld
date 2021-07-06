// Help.cpp
// Last update 6/7/2021 by Madman10K
#include "Help.hpp"
#include <imgui.h>
#ifndef PRODUCTION
void Help::display(bool& bShow)
{
    ImGui::Begin("Help", &bShow);

    constexpr char* link1 = (char*)"https://github.com/MadLadSquad/UntitledVulkanGameEngine\0";
    constexpr char* link2 = (char*)"https://github.com/MadLadSquad/UntitledVulkanGameEngine/wiki\0";
    constexpr char* link3 = (char*)"https://discord.gg/4wgH8ZE\0";

    ImGui::Text("Github Repo: ");
    ImGui::InputText("##in", link1, strlen(link1), ImGuiInputTextFlags_ReadOnly);

    ImGui::Text("Documentation: ");
    ImGui::InputText("##i", link2, strlen(link2), ImGuiInputTextFlags_ReadOnly);

    ImGui::Text("Discord Server: ");
    ImGui::InputText("##id", link3, strlen(link3),  ImGuiInputTextFlags_ReadOnly);

    if (ImGui::Button("Close##Help"))
    {
        bShow = false;
    }

    ImGui::End();
}
#endif