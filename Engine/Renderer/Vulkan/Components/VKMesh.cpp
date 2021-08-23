// VKMesh.cpp
// Last update 16/8/2021 by Madman10K
#include "VKMesh.hpp"
#include <utility>
#include <cstring>
#include "VKStructs.hpp"
#include "VKBuffer.hpp"

void UVK::VKMesh::create()
{
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    VKBuffer::createBuffer(*device, sizeof(VKVertex) * vertices.size(), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data = nullptr;
    vkMapMemory(device->logicalDevice, stagingBufferMemory, 0, sizeof(VKVertex) * vertices.size(), 0, &data);
    std::memcpy(data, vertices.data(), sizeof(VKVertex) * vertices.size());
    vkUnmapMemory(device->logicalDevice, stagingBufferMemory);

    VKBuffer::createBuffer(*device, sizeof(VKVertex) * vertices.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, deviceMemory);
    VKBuffer::copyBuffer(*device, *transferQueue, *transferCommandPool, stagingBuffer, vertexBuffer, sizeof(VKVertex) * vertices.size());

    vkDestroyBuffer(device->logicalDevice, stagingBuffer, nullptr);
    vkFreeMemory(device->logicalDevice, stagingBufferMemory, nullptr);

    stagingBuffer = VK_NULL_HANDLE;
    stagingBufferMemory = VK_NULL_HANDLE;
    data = nullptr;

    VKBuffer::createBuffer(*device, sizeof(uint32_t) * indices.size(), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    vkMapMemory(device->logicalDevice, stagingBufferMemory, 0, sizeof(uint32_t) * indices.size(), 0, &data);
    memcpy(data, indices.data(), sizeof(uint32_t) * indices.size());
    vkUnmapMemory(device->logicalDevice, stagingBufferMemory);

    VKBuffer::createBuffer(*device, sizeof(uint32_t) * indices.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexMemory);
    VKBuffer::copyBuffer(*device, *transferQueue, *transferCommandPool, stagingBuffer, indexBuffer, sizeof(uint32_t) * indices.size());
}

void UVK::VKMesh::render(const std::vector<VkCommandBuffer>& commandbuffers, const int& index, const std::vector<VkDescriptorSet>& descriptorSets)
{
    VkBuffer vertexBuffers[] = { vertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandbuffers[index], 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(commandbuffers[index], indexBuffer, 0, VK_INDEX_TYPE_UINT32);

    vkCmdBindDescriptorSets(commandbuffers[index], VK_PIPELINE_BIND_POINT_GRAPHICS, *pipelineLayout, 0, 1, &descriptorSets[index], 0, nullptr);

    vkCmdDrawIndexed(commandbuffers[index], indices.size(), 1, 0, 0, 0);
}

void UVK::VKMesh::clear()
{
    vkFreeMemory(device->logicalDevice, deviceMemory, nullptr);
    vkDestroyBuffer(device->logicalDevice, vertexBuffer, nullptr);
    vkFreeMemory(device->logicalDevice, indexMemory, nullptr);
    vkDestroyBuffer(device->logicalDevice, indexBuffer, nullptr);

    vertices.clear();
    indices.clear();
}

UVK::VKMesh::VKMesh(VKDevice* dev, VkQueue& transQueue, VkCommandPool& transCommandPool, std::vector<VKVertex> vert, std::vector<uint32_t> index, VkPipelineLayout& pipelineL)
{
    device = dev;
    vertices = std::move(vert);
    indices = std::move(index);
    transferCommandPool = &transCommandPool;
    transferQueue = &transQueue;
    pipelineLayout = &pipelineL;
}

VkBuffer& UVK::VKMesh::data()
{
    return vertexBuffer;
}
