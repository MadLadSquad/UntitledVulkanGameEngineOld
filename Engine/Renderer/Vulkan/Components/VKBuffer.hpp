// VKBuffer.hpp
// Last update 19/8/2021 by Madman10K
#pragma once
#ifndef __APPLE__
#include <vulkan/vulkan.h>

namespace UVK
{
    struct VKDevice;

    class VKBuffer
    {
    public:
        static void createBuffer(const VKDevice& device, uint64_t bufferSize, VkBufferUsageFlags bufferUsageFlags, VkMemoryPropertyFlags propertyFlags, VkBuffer& buffer, VkDeviceMemory& memory);
        static uint32_t calculateMemoryTypeIndex(const UVK::VKDevice& device, uint32_t types, VkMemoryPropertyFlags properties);
        static void copyBuffer(const VKDevice& device, VkQueue& transferQueue, VkCommandPool& transferCommandPool, VkBuffer& srcbuf, VkBuffer& dstbuf, VkDeviceSize bufferSize);
    };
}
#endif