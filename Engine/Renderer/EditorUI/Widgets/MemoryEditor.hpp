// MemoryEditor.hpp
// Last update 4/24/2021 by Madman10K
#pragma once
#include <imguiex/memory_editor/imgui_memory_editor.h>

namespace ImGuiMemoryEditor
{
    static void display()
    {
        ImGui::Begin("Memory Editor");
        int hello = 50;

        //ImGui::InputInt("Memory size", siz));

        static MemoryEditor mem_edit;

        mem_edit.DrawContents(&hello, sizeof(int));

        ImGui::End();
    }
}