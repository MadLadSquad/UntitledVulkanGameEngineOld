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
        ~VKDevice() noexcept;

        void createDevice(Swapchain& surface) noexcept;
        void destroyDevice() noexcept;

        VkDevice& getDevice() noexcept;
    private:
        friend class Swapchain;
        friend class VKMesh;

        QueueFamilyIndices createPhysicalDevice(Swapchain& surface) noexcept;

        VkQueue queue{};
        VkQueue presentationQueue{};
        VKInstance* instance{};
        VkDevice device{};
        VkPhysicalDevice physicalDevice{};
        QueueFamilyIndices indices;
    };
}
