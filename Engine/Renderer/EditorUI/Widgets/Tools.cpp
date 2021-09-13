// Tools.cpp
// Last update 13/9/2021 by Madman10K
#include "Tools.hpp"
#include <Renderer/EditorUI/Modules/EditorModule.hpp>
#include <imgui.h>

void Tools::display(const UVK::EditorModuleManager& module, bool& bShow)
{
    ImGui::Begin("Tools", &bShow);
    module.renderToolsModule();
    ImGui::End();
}