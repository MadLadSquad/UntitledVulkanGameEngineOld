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
        explicit VKDevice(VKInstance& instance) noexcept;
        ~VKDevice() = default;

        void createDevice(Swapchain& surface) noexcept;
        void destroyDevice() noexcept;

        VkDevice& getDevice() noexcept;
        VkPhysicalDevice& getPhysicalDevice() noexcept;
        VkQueue& getGraphicsQueue() noexcept;
        VkQueue& getPresentationQueue() noexcept;
        QueueFamilyIndices& getIndices() noexcept;
    private:
        friend class Swapchain;
        friend class VKBuffer;
        friend class VKMesh;

        QueueFamilyIndices createPhysicalDevice(Swapchain& surface) noexcept;

        VkPhysicalDeviceProperties deviceProperties{};

        VkQueue queue{};
        VkQueue presentationQueue{};
        VKInstance* instance{};
        VkDevice device{};
        VkPhysicalDevice physicalDevice{};
        QueueFamilyIndices indices;
    };
}
