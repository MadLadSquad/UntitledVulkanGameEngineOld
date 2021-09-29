// MemoryEditor.cpp
// Last update 15/6/2021 by Madman10K
#include "MemoryEditor.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <imguiex/memory_editor/imgui_memory_editor.h>

void ImGuiMemoryEditor::display(bool& bShow)
{
    ImGui::Begin("Memory Editor", &bShow);
    int hello = 50;

    static MemoryEditor mem_edit;

    mem_edit.DrawContents(&hello, sizeof(int));

    ImGui::End();
}
#endif