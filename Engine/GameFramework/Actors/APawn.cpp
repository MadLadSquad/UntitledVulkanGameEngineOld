// APawn.cpp
// Last update 21/7/2021 by Madman10K
#include <GL/glew.h>
#include "APawn.hpp"

void UVK::APawn::destroyPawn(APawn* pw)
{
    pw->endPlay();
    delete pw;
}