// TerminalEmulator.cpp
// Last update 15/5/2021 by Madman10K
#include "TerminalEmulator.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

void TerminalEmulator::display(std::string& terminalCommand, bool& bFinalisedCommand, bool& bShow)
{
    ImGui::Begin("Terminal Emulator", &bShow);
    ImGui::InputText("TTY command", &terminalCommand);
    ImGui::SameLine();
    if (ImGui::Button("Send##TTY"))
    {
        bFinalisedCommand = true;
    }

    //auto a = ImTTY::Terminal.DrawContents(terminalCommand, bFinalisedCommand);

    //ImGui::Text("%s", a.c_str());

    ImGui::End();
}