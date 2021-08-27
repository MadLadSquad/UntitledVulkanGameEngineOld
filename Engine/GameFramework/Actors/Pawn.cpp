// Pawn.cpp
// Last update 27/8/2021 by Madman10K
#include "Pawn.hpp"

void UVK::Pawn::destroyPawn(Pawn* pw)
{
    pw->endPlay();
    delete pw;
}