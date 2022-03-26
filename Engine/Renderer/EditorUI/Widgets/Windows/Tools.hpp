#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
namespace UVK
{
    class EditorModuleManager;
}

namespace Tools
{
    bool display(const UVK::EditorModuleManager& module, bool& bShow) noexcept;
}
#endif