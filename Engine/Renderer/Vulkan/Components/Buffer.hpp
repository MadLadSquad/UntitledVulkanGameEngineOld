#pragma once
#include "Device.hpp"

namespace UVK
{
    class VKBuffer
    {
    public:
        void create(VKDevice& dev, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsageFlags, VkMemoryPropertyFlags propertyFlags) noexcept;
        void destroy() noexcept;
        void copy(VkQueue transferQueue, VkCommandPool transferCommandPool, VKBuffer& buf) noexcept;

        VkDeviceMemory& getMemory() noexcept;
        VkBuffer& getBuffer() noexcept;
    private:
        VkBuffer buffer{};
        VkDeviceMemory memory{};
        VkDeviceSize bufferSz{};

        VKDevice* device = nullptr;
        uint32_t findMemoryTypeIndex(uint32_t allowedTypes, VkMemoryPropertyFlags properties) noexcept;
    };
}