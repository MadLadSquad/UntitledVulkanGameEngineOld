// TerminalEmulator.hpp
// Last update 5/5/2021 by Madman10K
#pragma once
#include <iostream>
#include <Core.hpp>
#include <imguiex/imtty/ImTTY.h>
#include <cpp/imgui_stdlib.h>

namespace TerminalEmulator
{
    void display(std::string& terminalCommand, bool& bFinalisedCommand);
}