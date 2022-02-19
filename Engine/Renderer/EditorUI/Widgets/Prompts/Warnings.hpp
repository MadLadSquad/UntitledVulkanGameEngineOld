// Warnings.hpp
// Last update 18/2/2022 by Madman10K
#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
namespace Warnings
{
    void displaySaveWarning(bool& bOpen);
    void displayGenerateWarning(bool& bOpen);
    void displayExitWarning(bool& bOpen);
}
#endif