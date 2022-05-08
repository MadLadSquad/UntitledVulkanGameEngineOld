#include "TerminalEmulator.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

bool TerminalEmulator::display(UVK::FString& terminalCommand, bool& bFinalisedCommand, bool& bShow) noexcept
{
    bool bReturn = false;
    ImGui::Begin("Terminal Emulator", &bShow);
    if (ImGui::InputText("TTY command", &terminalCommand) || ImGui::IsItemActive())
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