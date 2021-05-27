// VKStructs.hpp
// Last update 27/5/2021 by Madman10K
#pragma once
#include <vulkan/vulkan.h>

namespace UVK
{
    struct VKDevice
    {
        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
    };

    struct VKQueueFamilyLocation
    {
        int graphicsFamily = -1;

        [[nodiscard]] bool isValid() const
        {
            return graphicsFamily >= 0;
        }
    };
}