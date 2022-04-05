#include "Resources.hpp"
#include "Buffer.hpp"

void UVK::VKResources::createUniformBuffers(size_t dependencySizeLink) noexcept
{
    VkDeviceSize size = sizeof(VP);
    //VkDeviceSize modelSize = modelUniformAlignment * VK_MAX_OBJECTS;

    uniformBuffers.resize(dependencySizeLink);
    dynamicUniformBuffers.resize(dependencySizeLink);

    for (size_t i = 0; i < dependencySizeLink; i++)
    {
        uniformBuffers[i].create(*device, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        //dynamicUniformBuffers[i].create(*device, modelSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    }
}

void UVK::VKResources::updateUniformBuffers(UVK::VP& mvp, uint32_t imageIndex) noexcept
{
    void* data;
    vkMapMemory(device->getDevice(), uniformBuffers[imageIndex].getMemory(), 0, sizeof(VP), 0, &data);
    memcpy(data, &mvp, sizeof(VP));
    vkUnmapMemory(device->getDevice(), uniformBuffers[imageIndex].getMemory());

    //for (size_t i = 0; i < meshes.size(); i++)
    //{
    //    // What the fuck is this retardation
    //    auto* model = (Model*)((uint64_t)modelTransferSpace + (i * modelUniformAlignment));
    //    *model = meshes[i].model;
    //}
//
    //vkMapMemory(device->getDevice(), dynamicUniformBuffers[imageIndex].getMemory(), 0, modelUniformAlignment * meshes.size(), 0, &data);
    //memcpy(data, modelTransferSpace, modelUniformAlignment * meshes.size());
    //vkUnmapMemory(device->getDevice(), dynamicUniformBuffers[imageIndex].getMemory());
}

void UVK::VKResources::destroyUniformBuffers() noexcept
{
    for (size_t i = 0; i < uniformBuffers.size(); i++)
    {
        uniformBuffers[i].destroy();
        //dynamicUniformBuffers[i].destroy();
    }
}

void UVK::VKResources::allocateDynamicUniformBufferTransferSpace() noexcept
{
    // weird bit magic
    //modelUniformAlignment = (sizeof(Model) + device->deviceProperties.limits.minUniformBufferOffsetAlignment - 1) & ~(device->deviceProperties.limits.minUniformBufferOffsetAlignment - 1);
    //modelTransferSpace = (Model*)aligned_alloc(modelUniformAlignment, modelUniformAlignment * VK_MAX_OBJECTS);
}

void UVK::VKResources::freeDynamicUniformBufferTransferSpace() noexcept
{
    //free(modelTransferSpace);
}

UVK::VKResources::VKResources(VKDevice& dev) noexcept
{
    device = &dev;
}

std::vector<UVK::VKBuffer>& UVK::VKResources::getUniformBuffers() noexcept
{
    return uniformBuffers;
}
