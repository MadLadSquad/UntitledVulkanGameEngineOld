// VKDevice.hpp
// Last update 28/5/2021 by Madman10K
#pragma once
#include <vulkan/vulkan.h>
#include "../Components/VKStructs.hpp"
#include "VKSwapchain.hpp"

namespace UVK
{
    class Device
    {
    public:
        Device() = default;

        void set(VkInstance* inst, VKSwapchain* swap);
        void destroyLogicalDevice() const;

        VKDevice& getDevice();
    private:
        void getPhysicalDevice();
        void createLogicalDevice();

        bool checkDeviceSuitability(const VkPhysicalDevice& physicalDevice);
        [[nodiscard]] bool checkDeviceExtensionSupport() const;
        [[nodiscard]] UVK::VKQueueFamilyLocation getQueueFamilies() const;

        VKSwapchain* swapchain;
        VkInstance* instance;

        VKDevice device;
        VkQueue queue;
        VkQueue presentationQueue;
    };
}