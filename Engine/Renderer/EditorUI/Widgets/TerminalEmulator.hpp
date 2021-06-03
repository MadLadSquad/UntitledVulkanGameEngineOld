// TerminalEmulator.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <iostream>
#include <Core.hpp>

/**
 * @brief A terminal emulator widget
 */
namespace TerminalEmulator
{
    void display(std::string& terminalCommand, bool& bFinalisedCommand, bool& bShow);
}