// TerminalEmulator.hpp
// Last update 15/5/2021 by Madman10K
#pragma once
#include <iostream>
#include <Core.hpp>


namespace TerminalEmulator
{
    void display(std::string& terminalCommand, bool& bFinalisedCommand, bool& bShow);
}