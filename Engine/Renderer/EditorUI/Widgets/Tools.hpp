// Tools.hpp
// Last update 13/9/2021 by Madman10K
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