#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
namespace Warnings
{
    void displaySaveWarning(bool& bOpen) noexcept;
    void displayGenerateWarning(bool& bOpen) noexcept;
    void displayExitWarning(bool& bOpen) noexcept;
}
#endif