#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
/**
 * @brief Just a memory editor without a purpose
 */
namespace ImGuiMemoryEditor
{
    bool display(bool& bShow) noexcept;
}
#endif