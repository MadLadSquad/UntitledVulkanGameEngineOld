// GameInstanceInterface.cpp
// Last update 25/7/2021 by Madman10K
#include "GameInstanceInterface.hpp"
#include <Core/Global.hpp>

void UVK::Instance::exit()
{
    global.instance->exit();
}
