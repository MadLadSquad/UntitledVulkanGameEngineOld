// VulkanRenderer.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "Components/VKStructs.hpp"
#include <vulkan/vulkan.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace UVK
{
    class VulkanRenderer
    {
    public:
        VulkanRenderer() = default;

        void run();
    private:
        void start();
        void render();
        void cleanup();

        VkInstance instance;
        void createInstance();
        void destroyInstance();

        VKDevice device;
        void getPhysicalDevice();
        void createLogicalDevice();
        void destroyLogicalDevice() const;

        VkQueue queue;
        VkQueue presentationQueue;

        VkSurfaceKHR surface;
        void createSurface();
        void destroySurface();


        static bool checkExtensionSupport(std::vector<const char*>* extensions);
        bool checkDeviceSuitability(VkPhysicalDevice physicalDevice);
        [[nodiscard]] VKQueueFamilyLocation getQueueFamilies() const;
        bool checkDeviceExtensionSupport() const;
        VKSwapchainSettings getSwapchainSettings();
    };
}