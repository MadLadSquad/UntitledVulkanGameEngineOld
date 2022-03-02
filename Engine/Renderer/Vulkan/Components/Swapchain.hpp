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
        ~Swapchain();

        void createSwapchain();
        void destroySwapchain();

        void createSurface();
        void destroySurface();

        VkSurfaceKHR& getSurface();
    private:
        friend class VKDevice;
        bool getSwapchainDetails(VkPhysicalDevice& device);

        VkImageView createImageView(const VkImage& image, const VkFormat& format, const VkImageAspectFlags& aspectFlags);

        void determineSurfaceFormats();
        void determinePresentationMode();
        void determineExtent();

        SwapchainDetails details;
        VkSurfaceKHR surface{};
        VkSwapchainKHR swapchain{};

        VKInstance* instance = nullptr;
        VKDevice* device = nullptr;

        VkSurfaceFormatKHR surfaceFormat{};
        VkPresentModeKHR presentationMode;
        VkExtent2D extent{};

        std::vector<SwapchainImage> swapchainImages;
    };
}