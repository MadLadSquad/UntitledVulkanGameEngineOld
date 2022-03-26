#pragma once
#include <Generated/BuildDef.hpp>

#ifndef PRODUCTION
namespace Shipping
{
    bool display(bool& bShow, const std::string& prjname) noexcept;
}
#endif