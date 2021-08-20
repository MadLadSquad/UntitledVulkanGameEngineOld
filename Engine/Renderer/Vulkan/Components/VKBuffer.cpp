// VKBuffer.cpp
// Last update 19/8/2021 by Madman10K
#include "VKBuffer.hpp"
#include "VKStructs.hpp"

void UVK::VKBuffer::createBuffer(const UVK::VKDevice& device, uint64_t bufferSize, VkBufferUsageFlags bufferUsageFlags, VkMemoryPropertyFlags propertyFlags, VkBuffer& buffer, VkDeviceMemory& memory)
{
    VkBufferCreateInfo bufferInfo =
    {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = bufferSize,
        .usage = bufferUsageFlags,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };

    if (vkCreateBuffer(device.logicalDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan vertex buffer!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    VkMemoryRequirements memoryRequirements = {};
    vkGetBufferMemoryRequirements(device.logicalDevice, buffer, &memoryRequirements);

    VkMemoryAllocateInfo memoryAllocateInfo =
    {
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .allocationSize = memoryRequirements.size,
            .memoryTypeIndex = calculateMemoryTypeIndex(device, memoryRequirements.memoryTypeBits, propertyFlags)
    };

    if (vkAllocateMemory(device.logicalDevice, &memoryAllocateInfo, nullptr, &memory) != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't allocate memory for device!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    vkBindBufferMemory(device.logicalDevice, buffer, memory, 0);
}

uint32_t UVK::VKBuffer::calculateMemoryTypeIndex(const UVK::VKDevice& device, uint32_t types, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memoryProperties = {};
    vkGetPhysicalDeviceMemoryProperties(device.physicalDevice, &memoryProperties);

    for (auto i = 0; i < memoryProperties.memoryTypeCount; i++)
    {
        if ((types & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties)) // type index needs to match the corresponding bit in types
        {
            return i;
        }
    }

    logger.consoleLog("Couldn't find a compatible vertex buffer memory type!", UVK_LOG_TYPE_ERROR);
    throw std::runtime_error(" ");
}

void UVK::VKBuffer::copyBuffer(const UVK::VKDevice& device, VkQueue& transferQueue, VkCommandPool& transferCommandPool, VkBuffer& srcbuf, VkBuffer& dstbuf, VkDeviceSize bufferSize)
{
    VkCommandBuffer transferCommandBuffer;
    VkCommandBufferAllocateInfo allocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = transferCommandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };

    vkAllocateCommandBuffers(device.logicalDevice, &allocateInfo, &transferCommandBuffer);

    VkCommandBufferBeginInfo beginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };

    vkBeginCommandBuffer(transferCommandBuffer, &beginInfo);

    VkBufferCopy bufferCopyRegion =
    {
        .srcOffset = 0,
        .dstOffset = 0,
        .size = bufferSize
    };

    vkCmdCopyBuffer(transferCommandBuffer, srcbuf, dstbuf, 1, &bufferCopyRegion);
    vkEndCommandBuffer(transferCommandBuffer);

    VkSubmitInfo submitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .commandBufferCount = 1,
        .pCommandBuffers = &transferCommandBuffer
    };

    vkQueueSubmit(transferQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(transferQueue);

    vkFreeCommandBuffers(device.logicalDevice, transferCommandPool, 1, &transferCommandBuffer);
}
