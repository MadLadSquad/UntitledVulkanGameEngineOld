// Tools.cpp
// Last update 13/9/2021 by Madman10K
#include "Tools.hpp"
#ifndef PRODUCTION
#include <Renderer/EditorUI/Modules/EditorModule.hpp>
#include <imgui.h>

void Tools::display(const UVK::EditorModuleManager& module, bool& bShow)
{
    static UVK::CurrentToolType currentToolType = UVK::CURRENT_TOOL_TYPE_USEFUL_OBJECTS;

    ImGui::Begin("Tools", &bShow);

    ImGui::Columns(3, nullptr, false);
    if (ImGui::Selectable("Objects"))
        currentToolType = UVK::CURRENT_TOOL_TYPE_USEFUL_OBJECTS;
    ImGui::NextColumn();
    if (ImGui::Selectable("Terrain"))
        currentToolType = UVK::CURRENT_TOOL_TYPE_TERRAIN_EDITOR;
    ImGui::NextColumn();
    if (ImGui::Selectable("Custom"))
        currentToolType = UVK::CURRENT_TOOL_TYPE_CUSTOM;
    ImGui::Columns(1);
    ImGui::Separator();

    switch (currentToolType)
    {
    case UVK::CURRENT_TOOL_TYPE_USEFUL_OBJECTS:
        ImGui::TextWrapped("Useful objects coming soon!");
        break;
    case UVK::CURRENT_TOOL_TYPE_TERRAIN_EDITOR:
        ImGui::TextWrapped("Terrain editor coming soon!");
        break;
    default:
        break;
    }
    module.renderToolsModule(currentToolType);

    ImGui::End();
}
#endif