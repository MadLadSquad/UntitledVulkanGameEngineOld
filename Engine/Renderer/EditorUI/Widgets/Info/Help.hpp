#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
namespace Help
{
    // Displays help message
    void display(bool& bShow) noexcept;
}
#endif