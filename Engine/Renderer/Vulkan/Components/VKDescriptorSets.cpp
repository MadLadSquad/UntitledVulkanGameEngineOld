// VKDescriptorSets.cpp
// Last update 22/8/2021 by Madman10K
#include "VKDescriptorSets.hpp"
#ifndef __APPLE__
#include "VKStructs.hpp"
#include "../Pipeline/VKSwapchain.hpp"
#include "VKBuffer.hpp"
#include "UVKLog.h"

void UVK::VKDescriptorSets::createDescriptorSetLayout()
{
    constexpr VkDescriptorSetLayoutBinding descriptorSetLayoutBinding =
    {
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
        .pImmutableSamplers = nullptr
    };

    const VkDescriptorSetLayoutCreateInfo layoutCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 0,
        .pBindings = &descriptorSetLayoutBinding
    };

    if (vkCreateDescriptorSetLayout(device->logicalDevice, &layoutCreateInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan Descriptor Set Layout!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}

UVK::VKDescriptorSets::VKDescriptorSets(UVK::VKDevice& dev, VKSwapchain& swap)
{
    device = &dev;
    swapchain = &swap;
}

void UVK::VKDescriptorSets::destroyDescriptorSetLayout()
{
    vkDestroyDescriptorPool(device->logicalDevice, descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(device->logicalDevice, descriptorSetLayout, nullptr);

    for (size_t i = 0; i < uniformBuffers.size(); i++)
    {
        vkDestroyBuffer(device->logicalDevice, uniformBuffers[i], nullptr);
        vkFreeMemory(device->logicalDevice, uniformBufferMemory[i], nullptr);
    }
}

VkDescriptorSetLayout& UVK::VKDescriptorSets::layout()
{
    return descriptorSetLayout;
}

void UVK::VKDescriptorSets::createUniformBuffers()
{
    uniformBuffers = std::vector<VkBuffer>(swapchain->images.size());
    uniformBufferMemory = std::vector<VkDeviceMemory>(swapchain->images.size());

    for (size_t i = 0; i < swapchain->images.size(); i++)
    {
        VKBuffer::createBuffer(*device, sizeof(glm::mat4) * 3, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBufferMemory[i]);
    }
}

void UVK::VKDescriptorSets::createDescriptorPool()
{
    const VkDescriptorPoolSize poolSize =
    {
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = (uint32_t)uniformBuffers.size()
    };

    const VkDescriptorPoolCreateInfo poolCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = (uint32_t)uniformBuffers.size(),
        .poolSizeCount = 1,
        .pPoolSizes = &poolSize
    };

    if (vkCreateDescriptorPool(device->logicalDevice, &poolCreateInfo, nullptr, &descriptorPool) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to create a Vulkan Descriptor Pool!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }
}

void UVK::VKDescriptorSets::createDescriptorSets()
{
    descriptorSets = std::vector<VkDescriptorSet>(uniformBuffers.size());

    std::vector<VkDescriptorSetLayout> descriptorSetLayouts(uniformBuffers.size(), descriptorSetLayout);

    const VkDescriptorSetAllocateInfo setAllocateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = descriptorPool,
        .descriptorSetCount = (uint32_t)uniformBuffers.size(),
        .pSetLayouts = descriptorSetLayouts.data()
    };

    if (vkAllocateDescriptorSets(device->logicalDevice, &setAllocateInfo, descriptorSets.data()) != VK_SUCCESS)
    {
        logger.consoleLog("Failed to allocate Vulkan Descriptor Sets!", UVK_LOG_TYPE_ERROR);
        throw std::runtime_error(" ");
    }

    for (size_t i = 0; i < uniformBuffers.size(); i++)
    {
        const VkDescriptorBufferInfo mvpDescriptorBufferInfo =
        {
            .buffer = uniformBuffers[i],
            .offset = 0,
            .range = sizeof(glm::mat4) * 3
        };

        const VkWriteDescriptorSet mvpDescriptorSetWrite =
        {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet = descriptorSets[i],
            .dstBinding = 0,
            .dstArrayElement = 0,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .pBufferInfo = &mvpDescriptorBufferInfo
        };

        vkUpdateDescriptorSets(device->logicalDevice, 1, &mvpDescriptorSetWrite, 0, nullptr);
    }
}

const std::vector<VkDescriptorSet> &UVK::VKDescriptorSets::getDescriptorSets()
{
    return descriptorSets;
}

#endif