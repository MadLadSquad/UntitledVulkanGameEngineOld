// VKUtility.cpp
// Last update 26/02/2022 by Madman10K
#include "Utility.hpp"

bool UVK::QueueFamilyIndices::valid()
{
    return graphicsFamily >= 0 && presentationFamily >= 0;
}
