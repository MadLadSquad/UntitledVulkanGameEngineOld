// TerminalEmulator.cpp
// Last update 17/10/2021 by Madman10K
#include "TerminalEmulator.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

bool TerminalEmulator::display(std::string& terminalCommand, bool& bFinalisedCommand, bool& bShow)
{
    bool bReturn = false;
    ImGui::Begin("Terminal Emulator", &bShow);
    if (ImGui::InputText("TTY command", &terminalCommand) || ImGui::IsItemFocused())
        bReturn = true;
    ImGui::SameLine();
    if (ImGui::Button("Send##TTY"))
        bFinalisedCommand = true;

    //auto a = ImTTY::Terminal.DrawContents(terminalCommand, bFinalisedCommand);

    //ImGui::Text("%s", a.c_str());

    ImGui::End();
    return bReturn;
}
#endif