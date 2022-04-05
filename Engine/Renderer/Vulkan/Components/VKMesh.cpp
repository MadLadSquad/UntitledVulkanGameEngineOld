#include "VKMesh.hpp"

UVK::VKMesh::VKMesh(UVK::VKDevice& dev, VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<VKVertex> vertices, std::vector<uint32_t> indices) noexcept
{
    device = &dev;
    vertexNum = vertices.size();
    indexNum = indices.size();
    createVertexBuffer(transferQueue, transferCommandPool, vertices, indices);
}

const size_t& UVK::VKMesh::vertexCount() const noexcept
{
    return vertexNum;
}

UVK::VKBuffer& UVK::VKMesh::getVertexBuffer() noexcept
{
    return buffer;
}

void UVK::VKMesh::createVertexBuffer(VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<VKVertex>& vertices, std::vector<uint32_t>& indices) noexcept
{
    {
        VkDeviceSize bufferSize = sizeof(VKVertex) * vertices.size();
        VKBuffer stagingBuffer;
        stagingBuffer.create(*device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        void* data;
        vkMapMemory(device->device, stagingBuffer.getMemory(), 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), bufferSize);
        vkUnmapMemory(device->device, stagingBuffer.getMemory());

        buffer.create(*device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        stagingBuffer.copy(transferQueue, transferCommandPool, buffer);

        stagingBuffer.destroy();
    }
    VkDeviceSize bufferSize = sizeof(uint32_t) * indices.size();
    VKBuffer stagingBuffer;
    stagingBuffer.create(*device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    void* data;
    vkMapMemory(device->device, stagingBuffer.getMemory(), 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(device->device, stagingBuffer.getMemory());

    indexBuffer.create(*device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    stagingBuffer.copy(transferQueue, transferCommandPool, indexBuffer);

    stagingBuffer.destroy();
}

void UVK::VKMesh::destroyVertexBuffer() noexcept
{
    buffer.destroy();
    indexBuffer.destroy();
}

UVK::VKBuffer& UVK::VKMesh::getIndexBuffer() noexcept
{
    return indexBuffer;
}

const size_t& UVK::VKMesh::indexCount() const noexcept
{
    return indexNum;
}
