#pragma once
#include <vulkan/vulkan.h>
#include "Instance.hpp"
#include "Utility.hpp"

namespace UVK
{
    class Swapchain;
    class VKDevice
    {
    public:
        VKDevice() = default;
        /**
         * @brief Initialize the class
         * @param instance - The Global Vulkan instance
         */
        explicit VKDevice(VKInstance& instance) noexcept;
        ~VKDevice() = default;

        /**
         * @brief Create the Device
         * @param surface - The surface for which to create it
         */
        void createDevice(Swapchain& surface) noexcept;
        void destroyDevice() noexcept;

        VkDevice& getDevice() noexcept;
        VkPhysicalDevice& getPhysicalDevice() noexcept;
        VkQueue& getGraphicsQueue() noexcept;
        VkQueue& getPresentationQueue() noexcept;
        QueueFamilyIndices& getIndices() noexcept;
    private:
        friend class Swapchain;
        friend class VKResources;
        friend class VKBuffer;
        friend class VKMesh;

        /**
         * @brief Create the Physical Device
         * @param surface - The surface for which to create it
         * @return The queue family indices for the device
         */
        QueueFamilyIndices createPhysicalDevice(Swapchain& surface) noexcept;

        VkPhysicalDeviceProperties deviceProperties{};

        void setMSAASamples() const noexcept;

        VkQueue queue{};
        VkQueue presentationQueue{};
        VKInstance* instance{};
        VkDevice device{};
        VkPhysicalDevice physicalDevice{};
        QueueFamilyIndices indices;
    };
}
