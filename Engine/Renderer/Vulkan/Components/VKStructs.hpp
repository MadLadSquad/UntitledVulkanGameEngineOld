// VKStructs.hpp
// Last update 16/8/2021 by Madman10K
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
#include <Core/Types.hpp>

namespace UVK
{
    // array of extensions for the gpu
    constexpr std::array<const char*, 1> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    /**
     * @brief A GPU device struct
     */
    struct VKDevice
    {
    private:
        friend class VKPipeline;
        friend class VKCommandBuffers;
        friend class VKFramebuffer;
        friend class Device;
        friend class VKSwapchain;
        friend class VKShader;
        friend class VKGraphicsPipeline;
        friend class VKDraw;
        friend class VKMesh;
        friend class VKBuffer;
        friend class VKDescriptorSets;

        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
    };

    /**
     * @brief Vulkan queue family indices/locations
     */
    struct VKQueueFamilyLocation
    {
    private:
        friend class VKCommandBuffers;
        friend class Device;
        friend class VKSwapchain;

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
    private:
        friend class VKSwapchain;
        friend class Device;

        VkSurfaceCapabilitiesKHR surfaceCapabilities{};
        std::vector<VkSurfaceFormatKHR> formats{};
        std::vector<VkPresentModeKHR> presentationModes{};
    };

    struct VKSwapchainImage
    {
    private:
        VKSwapchainImage() = default;
        VKSwapchainImage(VkImage img, VkImageView imgView)
            : image(img), imageView(imgView)
        {
        }

        friend class VKSwapchain;

        VkImage image;
        VkImageView imageView;
    };
}
#endif
