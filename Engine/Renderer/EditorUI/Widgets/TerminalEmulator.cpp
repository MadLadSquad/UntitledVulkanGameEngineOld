// TerminalEmulator.cpp
// Last update 5/5/2021 by Madman10K
#include "TerminalEmulator.hpp"

void TerminalEmulator::display(std::string& terminalCommand, bool& bFinalisedCommand)
{
    ImGui::Begin("Terminal Emulator", nullptr);

    ImGui::InputText("TTY command", &terminalCommand);
    ImGui::SameLine();
    if (ImGui::Button("Send##TTY"))
    {
        bFinalisedCommand = true;
    }

    auto a = ImTTY::Terminal.DrawContents(terminalCommand, bFinalisedCommand);

    ImGui::Text("%s", a.c_str());

    ImGui::End();
}