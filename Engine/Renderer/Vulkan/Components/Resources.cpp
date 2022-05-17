#include "Resources.hpp"
#include "Buffer.hpp"
#include <Core/Interfaces/ECSInterface.hpp>
#include <GameFramework/Components/Components/MeshComponent.hpp>
#include <GameFramework/Components/Components/MeshComponentRaw.hpp>
#include <Core/Actor.hpp>
#include <cstdlib>
#include <GameFramework/GameplayClasses/GameInstance.hpp>

void UVK::VKResources::createUniformBuffers(size_t dependencySizeLink) noexcept
{
    VkDeviceSize modelSize = modelUniformAlignment * VK_MAX_OBJECTS;

    uniformBuffers.resize(dependencySizeLink);
    if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
        dynamicUniformBuffers.resize(dependencySizeLink);

    for (size_t i = 0; i < dependencySizeLink; i++)
    {
        // Create the buffers
        uniformBuffers[i].create(*device, global.instance->initInfo.shaderConstantStruct.size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
            dynamicUniformBuffers[i].create(*device, modelSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    }
}

void UVK::VKResources::updateUniformBuffers(UVK::VP& mvp, uint32_t imageIndex) noexcept
{
    // Push standard data defined in the base shader struct automatically
    global.instance->initInfo.shaderConstantStruct.data->projection = mvp.projection;
    global.instance->initInfo.shaderConstantStruct.data->view = mvp.view;
    global.instance->initInfo.shaderConstantStruct.data->inverseViewMatrix = glm::inverse(mvp.view);

    // Get the GPU memory and copy the data from the struct to the uniform buffer
    void* data;
    vkMapMemory(device->getDevice(), uniformBuffers[imageIndex].getMemory(), 0, global.instance->initInfo.shaderConstantStruct.size, 0, &data);
    memcpy(data, (void*)global.instance->initInfo.shaderConstantStruct.data, global.instance->initInfo.shaderConstantStruct.size);
    vkUnmapMemory(device->getDevice(), uniformBuffers[imageIndex].getMemory());
    if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
    {
        // Update dynamic uniform buffers
        const auto& meshes = ECS::data().view<MeshComponent>();
        size_t i = 0;
        for (auto& a : meshes)
        {
            Actor act(a);
            auto& mesh = act.get<MeshComponent>();
            void* model = (void*)((uint64_t)modelTransferSpace + (i * modelUniformAlignment));
            global.instance->initInfo.shaderMutableStruct.updateDynamicUniformBufferCallback(model);
            i++;
        }
        const auto& raw = ECS::data().view<MeshComponentRaw>();
        for (auto& a : raw)
        {
            Actor act(a);
            auto& mesh = act.get<MeshComponentRaw>();
            void* model = (void*)((uint64_t)modelTransferSpace + (i * modelUniformAlignment));
            global.instance->initInfo.shaderMutableStruct.updateDynamicUniformBufferCallback(model);
            i++;
        }
        vkMapMemory(device->getDevice(), dynamicUniformBuffers[imageIndex].getMemory(), 0, modelUniformAlignment * meshes.size(), 0, &data);
        memcpy(data, modelTransferSpace, modelUniformAlignment * meshes.size());
        vkUnmapMemory(device->getDevice(), dynamicUniformBuffers[imageIndex].getMemory());
    }
}

void UVK::VKResources::destroyUniformBuffers() noexcept
{
    for (size_t i = 0; i < uniformBuffers.size(); i++)
    {
        uniformBuffers[i].destroy();
        if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
            dynamicUniformBuffers[i].destroy();
    }
}

void UVK::VKResources::allocateDynamicUniformBufferTransferSpace() noexcept
{
    if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
    {
        // weird bit magic
        modelUniformAlignment = (global.instance->initInfo.shaderMutableStruct.size + device->deviceProperties.limits.minUniformBufferOffsetAlignment - 1) & ~(device->deviceProperties.limits.minUniformBufferOffsetAlignment - 1);
        // Another rant centered at Windows here, ok so the C++ standard isn't fully compatible, I get it. But if you will make a function that mimics the standard, why do you switch the argument types???????????
#ifdef _WIN32
        modelTransferSpace = _aligned_malloc(modelUniformAlignment * VK_MAX_OBJECTS, modelUniformAlignment);
#else
        modelTransferSpace = aligned_alloc(modelUniformAlignment, modelUniformAlignment * VK_MAX_OBJECTS);
#endif
    }
}

void UVK::VKResources::freeDynamicUniformBufferTransferSpace() noexcept
{
    if (global.instance->initInfo.shaderMutableStruct.data != nullptr && global.instance->initInfo.shaderMutableStruct.size > 0)
    {
        // Weird free operations
#ifdef _WIN32
    _aligned_free(modelTransferSpace);
#else
    free(modelTransferSpace);
#endif
    }
}

std::vector<UVK::VKBuffer>& UVK::VKResources::getDynamicUniformBuffers() noexcept
{
    return dynamicUniformBuffers;
}

size_t& UVK::VKResources::getModelUniformAlignment() noexcept
{
    return modelUniformAlignment;
}

UVK::VKResources::VKResources(VKDevice& dev) noexcept
{
    device = &dev;
}

std::vector<UVK::VKBuffer>& UVK::VKResources::getUniformBuffers() noexcept
{
    return uniformBuffers;
}
