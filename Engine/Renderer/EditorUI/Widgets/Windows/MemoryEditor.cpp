#include "MemoryEditor.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <imguiex/memory_editor/imgui_memory_editor.h>

bool ImGuiMemoryEditor::display(bool& bShow) noexcept
{
    ImGui::Begin("Memory Editor", &bShow);
    int hello = 50;

    static MemoryEditor mem_edit;

    mem_edit.DrawContents(&hello, sizeof(int));

    ImGui::End();
    return false;
}
#endif