// TerminalEmulator.hpp
// Last update 4/24/2021 by Madman10K
#pragma once
#include <imguiex/imtty/ImTTY.h>
#include <cpp/imgui_stdlib.h>

namespace TerminalEmulator
{
    static void display(std::string& terminalCommand, bool& bFinalisedCommand)
    {
        ImGui::Begin("Terminal Emulator");

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
}