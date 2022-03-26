#include "VKMesh.hpp"

UVK::VKMesh::VKMesh(UVK::VKDevice& dev, std::vector<VKVertex> vertices) noexcept
{
    device = &dev;
    vertexNum = vertices.size();
    createVertexBuffer(vertices);
}

const size_t& UVK::VKMesh::vertexCount() const noexcept
{
    return vertexNum;
}

VkBuffer& UVK::VKMesh::getVertexBuffer() noexcept
{
    return vertexBuffer;
}

void UVK::VKMesh::createVertexBuffer(std::vector<VKVertex>& vertices) noexcept
{
    const VkBufferCreateInfo bufferInfo =
    {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = sizeof(VKVertex) * vertices.size(),
        .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };

    auto result = vkCreateBuffer(device->getDevice(), &bufferInfo, nullptr, &vertexBuffer);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't create a vertex buffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device->getDevice(), vertexBuffer, &memoryRequirements);

    const VkMemoryAllocateInfo memoryAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = findMemoryTypeIndex(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
    };

    result = vkAllocateMemory(device->device, &memoryAllocateInfo, nullptr, &deviceMemory);
    if (result != VK_SUCCESS)
    {
        logger.consoleLog("Couldn't allocate memory for the vertex buffer! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    vkBindBufferMemory(device->device, vertexBuffer, deviceMemory, 0);

    void* data;
    vkMapMemory(device->device, deviceMemory, 0, bufferInfo.size, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferInfo.size);
    vkUnmapMemory(device->device, deviceMemory);
}

void UVK::VKMesh::destroyVertexBuffer() noexcept
{
    vkDestroyBuffer(device->getDevice(), vertexBuffer, nullptr);
    vkFreeMemory(device->device, deviceMemory, nullptr);
}

uint32_t UVK::VKMesh::findMemoryTypeIndex(uint32_t allowedTypes, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(device->physicalDevice, &memoryProperties);

    // Used for checking if the bit is in allowed types
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
        if ((allowedTypes & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
            return i;
}
