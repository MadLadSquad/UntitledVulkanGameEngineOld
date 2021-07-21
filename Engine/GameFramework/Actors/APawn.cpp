// APawn.cpp
// Last update 21/7/2021 by Madman10K
#include "APawn.hpp"

void UVK::destroyPawn(APawn* pw)
{
    pw->endPlay();
    delete pw;
}