// VKUtility.hpp
// Last update 26/02/2022 by Madman10K
#pragma once
#include <array>

namespace UVK
{
    constexpr std::array<const char*, 1> deviceExtensions =
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    struct SwapchainDetails
    {
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        std::vector<VkSurfaceFormatKHR> surfaceFormats;
        std::vector<VkPresentModeKHR> presentationModes;
    };

    class VKUtility
    {
    public:

    };

    struct QueueFamilyIndices
    {
        int graphicsFamily = -1;
        int presentationFamily = -1;

        bool valid();
    };
}