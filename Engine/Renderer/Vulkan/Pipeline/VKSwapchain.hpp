// VKSwapchain.hpp
// Last update 28/5/2021 by Madman10K
#pragma once
#include <vulkan/vulkan.h>
#include "../Components/VKStructs.hpp"
#include "VKInstance.hpp"

namespace UVK
{
    class Device;

    class VKSwapchain
    {
    public:
        VKSwapchain() = default;

        void set(VKInstance* inst, Device* dev);

        void createSurface();
        void destroySurface();

        void createSwapchain();
        void destroySwapchain();

        VKSwapchainSettings getSwapchainSettings();

        VkSurfaceKHR& getSurface()
        {
            return surface;
        }
    private:
        VkSurfaceKHR surface;
        VKInstance* instance;
        Device* device;
    };
}