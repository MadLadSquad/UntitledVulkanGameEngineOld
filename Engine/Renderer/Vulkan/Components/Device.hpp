// Device.hpp
// Last update 21/12/2021 by Madman10K
#pragma once
#include <vulkan/vulkan.h>
#include "Instance.hpp"
#include "Utility.hpp"

namespace UVK
{
    class VKDevice
    {
    public:
        VKDevice() = default;
        explicit VKDevice(VKInstance& instance);
        ~VKDevice() = default;

        void createDevice();
        void destroyDevice();

        VkDevice& getDevice();
        VkPhysicalDevice& getPhysicalDevice();
    private:
        QueueFamilyIndices createPhysicalDevice();

        VKInstance* instance;
        VkDevice device;
        VkPhysicalDevice physicalDevice;
    };
}
