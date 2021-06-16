// TerminalEmulator.hpp
// Last update 15/6/2021 by Madman10K
#pragma once
#include <iostream>
#include <Core.hpp>

#ifndef PRODUCTION
/**
 * @brief A terminal emulator widget
 */
namespace TerminalEmulator
{
    void display(std::string& terminalCommand, bool& bFinalisedCommand, bool& bShow);
}
#endif