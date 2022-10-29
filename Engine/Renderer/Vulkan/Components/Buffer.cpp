#include "Buffer.hpp"

void UVK::VKBuffer::create(UVK::VKDevice& dev, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsageFlags, VkMemoryPropertyFlags propertyFlags) noexcept
{
    device = &dev;
    bufferSz = bufferSize;
    // The template for creating a Vulkan buffer
    const VkBufferCreateInfo bufferInfo =
    {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = bufferSize,
        .usage = bufferUsageFlags,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE        // Not supporting concurrent buffer access
    };

    // Create the buffer duh
    auto result = vkCreateBuffer(dev.getDevice(), &bufferInfo, nullptr, &buffer);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't create a vertex buffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device->getDevice(), buffer, &memoryRequirements);

    const VkMemoryAllocateInfo memoryAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = findMemoryTypeIndex(memoryRequirements.memoryTypeBits, propertyFlags)
    };

    // Allocate the memory duh
    result = vkAllocateMemory(dev.getDevice(), &memoryAllocateInfo, nullptr, &memory);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't allocate memory for the vertex buffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    // Bind the buffer memory to be ussed by the buffer
    vkBindBufferMemory(dev.getDevice(), buffer, memory, 0);
}

void UVK::VKBuffer::destroy() noexcept
{
    vkDestroyBuffer(device->getDevice(), buffer, nullptr);
    vkFreeMemory(device->device, memory, nullptr);
}

uint32_t UVK::VKBuffer::findMemoryTypeIndex(uint32_t allowedTypes, VkMemoryPropertyFlags properties) noexcept
{
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(device->physicalDevice, &memoryProperties);

    // Used for checking if the bit is in allowed types
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
        if ((allowedTypes & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
            return i;
    std::terminate();
}

VkDeviceMemory& UVK::VKBuffer::getMemory() noexcept
{
    return memory;
}

VkBuffer& UVK::VKBuffer::getBuffer() noexcept
{
    return buffer;
}

void UVK::VKBuffer::copy(VkQueue transferQueue, VkCommandPool transferCommandPool, UVK::VKBuffer& buf) noexcept
{
    auto transferCommandBuffer = beginCommandBuffer(transferCommandPool, *device);

    const VkBufferCopy bufferCopy =
    {
        .srcOffset = 0,
        .dstOffset = 0,
        .size = bufferSz
    };

    buf.bufferSz = bufferSz;
    vkCmdCopyBuffer(transferCommandBuffer, buffer, buf.buffer, 1, &bufferCopy);
    endCommandBuffer(transferQueue, transferCommandPool, transferCommandBuffer, *device);
}

VkCommandBuffer UVK::VKBuffer::beginCommandBuffer(VkCommandPool transferCommandPool, VKDevice& device) noexcept
{
    VkCommandBuffer transferCommandBuffer;
    const VkCommandBufferAllocateInfo commandBufferAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = transferCommandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1,
    };
    vkAllocateCommandBuffers(device.getDevice(), &commandBufferAllocateInfo, &transferCommandBuffer);

    constexpr VkCommandBufferBeginInfo beginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };

    vkBeginCommandBuffer(transferCommandBuffer, &beginInfo);
    return transferCommandBuffer;
}

void UVK::VKBuffer::endCommandBuffer(VkQueue transferQueue, VkCommandPool& transferCommandPool, VkCommandBuffer& transferCommandBuffer, VKDevice& device) noexcept
{
    vkEndCommandBuffer(transferCommandBuffer);

    const VkSubmitInfo submitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .commandBufferCount = 1,
        .pCommandBuffers = &transferCommandBuffer
    };

    vkQueueSubmit(transferQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(transferQueue);

    vkFreeCommandBuffers(device.device, transferCommandPool, 1, &transferCommandBuffer);
}

void UVK::VKBuffer::copyImageBuffer(VkQueue transferQueue, VkCommandPool transferCommandPool, VkImage image, FVector2 size) noexcept
{
    auto transferCommandBuffer = beginCommandBuffer(transferCommandPool, *device);

    const VkBufferImageCopy imageRegion =
    {
        .bufferOffset = 0,
        .bufferRowLength = 0,
        .bufferImageHeight = 0,
        .imageSubresource =
        {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .mipLevel = 0,
            .baseArrayLayer = 0,
            .layerCount = 1,
        },
        .imageOffset = { 0, 0, 0 },
        .imageExtent = { static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y), 1 }
    };

    vkCmdCopyBufferToImage(transferCommandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imageRegion);
    endCommandBuffer(transferQueue, transferCommandPool, transferCommandBuffer, *device);
}

void UVK::VKBuffer::transitionImageLayout(const VkQueue& queue, VkCommandPool& commandPool, const VkImage& image, VkImageLayout old, VkImageLayout newl, uint32_t mipLevels) noexcept
{
    auto commandBuffer = beginCommandBuffer(commandPool, *device);

    VkImageMemoryBarrier memoryBarrier =
    {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .oldLayout = old,
        .newLayout = newl,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = image,
        .subresourceRange =
        {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel = 0,
            .levelCount = mipLevels,
            .baseArrayLayer = 0,
            .layerCount = 1
        },
    };
    // TODO: ok so there is a minor code duplication thing here, ideally we should use variables and just call the vkCmdPipelineBarrier function once, but for some reason when using variable something fucks up
    // and the validation reports that they're 0?????? Anyway not that big of a deal
    if (old == VK_IMAGE_LAYOUT_UNDEFINED && newl == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
    {
        memoryBarrier.srcAccessMask = 0;
        memoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &memoryBarrier);
    }
    else if (old == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newl == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
        memoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        memoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &memoryBarrier);
    }
    endCommandBuffer(queue, commandPool, commandBuffer, *device);
}
