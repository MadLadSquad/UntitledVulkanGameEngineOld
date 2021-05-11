// MemoryEditor.cpp
// Last update 5/5/2021 by Madman10K
#include "MemoryEditor.hpp"

void ImGuiMemoryEditor::display()
{
    ImGui::Begin("Memory Editor");
    int hello = 50;

    static MemoryEditor mem_edit;

    mem_edit.DrawContents(&hello, sizeof(int));

    ImGui::End();
}