// MemoryEditor.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <imgui.h>
#include <imguiex/memory_editor/imgui_memory_editor.h>

#ifndef PRODUCTION
/**
 * @brief Just a memory editor without a purpose
 */
namespace ImGuiMemoryEditor
{
    void display(bool& bShow);
}
#endif