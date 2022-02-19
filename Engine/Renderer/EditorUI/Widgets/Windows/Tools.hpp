// Tools.hpp
// Last update 18/2/2022 by Madman10K
#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
namespace UVK
{
    class EditorModuleManager;
}

namespace Tools
{
    bool display(const UVK::EditorModuleManager& module, bool& bShow);
}
#endif