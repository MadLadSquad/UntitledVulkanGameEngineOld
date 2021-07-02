// VKSwapchain.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#ifndef __APPLE__
    #include <vulkan/vulkan.h>

#include "../Components/VKStructs.hpp"
#include "VKInstance.hpp"

namespace UVK
{
    class Device;

    /**
     * @brief Manages a Vulkan swapchain
     */
    class VKSwapchain
    {
    public:
        VKSwapchain() = default;
    private:
        friend class VKPipeline;
        friend class Device;

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

        VkSurfaceKHR surface;
        VKInstance* instance;
        Device* device;
    };
}
#endif
