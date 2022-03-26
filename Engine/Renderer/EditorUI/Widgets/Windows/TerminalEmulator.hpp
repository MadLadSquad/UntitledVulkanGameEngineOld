#pragma once
#include <iostream>
#include <Core.hpp>

#ifndef PRODUCTION
/**
 * @brief A terminal emulator widget
 */
namespace TerminalEmulator
{
    bool display(std::string& terminalCommand, bool& bFinalisedCommand, bool& bShow) noexcept;
}
#endif