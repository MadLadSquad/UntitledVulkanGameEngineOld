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
        void copyImageBuffer(VkQueue transferQueue, VkCommandPool transferCommandPool, VkImage image, FVector2 size) noexcept;

       static VkCommandBuffer beginCommandBuffer(VkCommandPool transferCommandPool, VKDevice& device) noexcept;
       static void endCommandBuffer(VkQueue transferQueue, VkCommandPool& transferCommandPool, VkCommandBuffer& transferCommandBuffer, VKDevice& device) noexcept;

        void transitionImageLayout(VkQueue& queue, VkCommandPool& commandPool, VkImage& image, VkImageLayout old, VkImageLayout newl, uint32_t mipLevels = 1) noexcept;

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