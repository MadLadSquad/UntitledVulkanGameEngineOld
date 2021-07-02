// VKDevice.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#ifndef __APPLE__
    #include <vulkan/vulkan.h>
#include "../Components/VKStructs.hpp"
#include "VKSwapchain.hpp"

namespace UVK
{
    /**
     * @brief A vulkan device class/manager not to be confused with VKDevice which is just a device struct
     */
    class Device
    {
    public:
        Device() = default;
    private:
        friend class VKPipeline;
        friend class VKSwapchain;

        void set(VkInstance* inst, VKSwapchain* swap);
        void destroyLogicalDevice() const;

        VKDevice& getDevice();

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
#endif
