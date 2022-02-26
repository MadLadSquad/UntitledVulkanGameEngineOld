// Swapchain.hpp
// Last update 26/02/2022 by Madman10K
#pragma once
#include "Instance.hpp"
#include "Utility.hpp"
#include "Device.hpp"

namespace UVK
{
    class Swapchain
    {
    public:
        Swapchain() = default;
        Swapchain(VKInstance& inst, VKDevice& dev);

        void createSurface();
        void destroySurface();

        VkSurfaceKHR& getSurface();
    private:
        friend class VKDevice;
        bool getSwapchainDetails(VkPhysicalDevice& device);

        SwapchainDetails details;
        VkSurfaceKHR surface{};
        VKInstance* instance = nullptr;
        VKDevice* device = nullptr;
    };
}