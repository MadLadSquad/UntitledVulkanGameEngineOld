#pragma once
#include <Generated/BuildDef.hpp>

#ifndef PRODUCTION
namespace Shipping
{
    bool display(bool& bShow, const UVK::FString& prjname) noexcept;
}
#endif