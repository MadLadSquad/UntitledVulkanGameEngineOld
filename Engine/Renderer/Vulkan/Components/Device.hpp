// Device.hpp
// Last update 26/02/2022 by Madman10K
#pragma once
#include <vulkan/vulkan.h>
#include "Instance.hpp"
#include "Utility.hpp"

namespace UVK
{
    class Swapchain;
    class VKDevice
    {
    public:
        VKDevice() = default;
        explicit VKDevice(VKInstance& instance);
        ~VKDevice();

        void createDevice(Swapchain& surface);
        void destroyDevice();

        VkDevice& getDevice();
        VkPhysicalDevice& getPhysicalDevice();
    private:
        friend class Swapchain;

        QueueFamilyIndices createPhysicalDevice(Swapchain& surface);

        VkQueue queue;
        VkQueue presentationQueue;
        VKInstance* instance;
        VkDevice device;
        VkPhysicalDevice physicalDevice;
        QueueFamilyIndices indices;
    };
}
