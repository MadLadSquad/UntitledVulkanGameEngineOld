// VKStructs.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#ifdef __APPLE__
namespace UVK
{
    constexpr std::array<const char*, 1> deviceExtensions = { "Apple" };
    struct VKDevice;
    struct VKQueueFamilyLcation;
    struct VKSwapchainSettings;
}
#else
#include <vulkan/vulkan.h>
#include <Core.hpp>

namespace UVK
{
    // array of extensions for the gpu
    constexpr std::array<const char*, 1> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    /**
     * @brief A GPU device struct
     */
    struct VKDevice
    {
        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
    };

    /**
     * @brief Vulkan queue family indices/locations
     */
    struct VKQueueFamilyLocation
    {
        int graphicsFamily = -1;
        int presentationFamily = -1;

        [[nodiscard]] bool isValid() const
        {
            return graphicsFamily >= 0 && presentationFamily >= 0;
        }
    };

    /**
     * @brief Settings about the swapchain
     */
    struct VKSwapchainSettings
    {
        VkSurfaceCapabilitiesKHR surfaceCapabilities{};
        std::vector<VkSurfaceFormatKHR> formats{};
        std::vector<VkPresentModeKHR> presentationModes{};
    };
}
#endif
