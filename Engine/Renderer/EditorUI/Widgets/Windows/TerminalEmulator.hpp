// TerminalEmulator.hpp
// Last update 18/2/2022 by Madman10K
#pragma once
#include <iostream>
#include <Core.hpp>

#ifndef PRODUCTION
/**
 * @brief A terminal emulator widget
 */
namespace TerminalEmulator
{
    bool display(std::string& terminalCommand, bool& bFinalisedCommand, bool& bShow);
}
#endif